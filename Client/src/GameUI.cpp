/*
 * GAMEUI.cpp
 *
 *  Created on: 30 de out de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameUI.hpp"

PlayerConsoleInput::PlayerConsoleInput(sf::Vector2f pos, sf::Vector2f size, std::string txt) : 
	EditBox(pos, size, txt, config::color_border, config::color_inside, sf::Color::White)
{
	
}

void PlayerConsoleInput::onResize(sf::Vector2f & new_size)
{
	size.x = new_size.x;
}

PlayerConsole::PlayerConsole() : UI::Element(sf::Vector2f(0, 0), sf::Vector2f(0, 0)), eb(PlayerConsoleInput(sf::Vector2f(0, size.y - DEFAULT_LABEL_WIDTH), sf::Vector2f(size.x, DEFAULT_LABEL_WIDTH), ""))
{
	isVisible = false;
}

PlayerConsole::~PlayerConsole()
{
	
}

void PlayerConsole::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, config::color_inside, config::color_border); //draw box
		eb.draw(window); //draw text being edited
		
		size_t num_elem = str.size(); //draw other element
		for(size_t i = 0; i < num_elem; i++) //iterate through strings
		{
			if(str[i].size() > 0) //if has text
			{
				drawText(window, sf::Vector2f(eb.pos.x + 3, eb.pos.y - 3 - config::txt_size*(i+1)), str[i], eb.size.y, sf::Color::White);
			}
			if(eb.pos.y - 3 - config::txt_size*(i+1) + 15 < 0)
			{
				str.erase(str.begin() + i, str.begin() + (num_elem-1));
				break;
			}
		}
	}
}

bool PlayerConsole::onEvent(sf::Event & event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::BackSlash || event.key.code == sf::Keyboard::Equal)
		{
			isVisible = !isVisible;
			return true;
		}
		
		if(isVisible)
		{
			if(event.key.code == sf::Keyboard::Return && eb.txt.size() > 0)
			{
				//TODO: get and run commands!
				Console::getConsole().log("Command is \"%s\"\n", eb.txt.c_str());
				if(eb.txt == "EXIT")
					exit(2);
				str.insert(str.begin(), eb.txt);
				eb.txt.resize(0);
				return true;
			}
			else
			{
				return eb.onEvent(event);
			}
		}
	}
	return false;
}

void PlayerConsole::onResize(sf::Vector2f & new_size)
{
	size.x = new_size.x;
	size.y = new_size.y/3;
	eb.pos = sf::Vector2f(0, size.y - config::txt_size); //resize input box
	eb.size = sf::Vector2f(size.x, config::txt_size);
}


ClosePopUp::ClosePopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : PopUp(pos,size, name)
{

}

void ClosePopUp::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, sf::Color(255,255,255,127), sf::Color(255,255,255,127));
		drawText(window, sf::Vector2f(size.x/2, size.y/2), "Exit? Y/N", 40, sf::Color::Blue, ALIGN_CENTER);
	}
}

bool ClosePopUp::onEvent(sf::Event & event)
{
	if(isVisible)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Y)
			{
				answer = true;
				return true;
			}
			else if(event.key.code == sf::Keyboard::N)
			{
				answer = false;
				isVisible = false;
				return true;
			}
		}
	}
	return false;
}

BeginPopUp::BeginPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : UI::PopUp(pos, size, name)
{
	isVisible = true;
}

void BeginPopUp::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, sf::Color::Black, sf::Color::Black);
		drawText(window, sf::Vector2f(size.x/2, size.y/2), "CollectiveAutomata", 50, sf::Color::Blue, ALIGN_CENTER);
	}
}

bool BeginPopUp::onEvent(sf::Event & event)
{
	if(isVisible)
	{
		if(event.type  ==  sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
			{
				isVisible = false;
				return true;
			}
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			if( (event.mouseButton.x >= pos.x && event.mouseButton.x < pos.x + size.x) && (event.mouseButton.y >= pos.y && event.mouseButton.y < pos.y + size.y) )
			{
				isVisible = false;
				return true;
			}
		}
		return true; //this will force feedback on begin popup!
	}
	return false;
}

EditorPopUp::EditorPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : UI::PopUp(pos, size, name)
{
	isVisible = false;
	amountElements = 5;
}
	
void EditorPopUp::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, config::color_inside, sf::Color::Black);
		drawText(window, sf::Vector2f(size.x/2, -3), "Editor", 25, sf::Color::Red, ALIGN_CENTER);
	}
}

bool EditorPopUp::onEvent(sf::Event & event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::F12)
		{
			isVisible = !isVisible;
			return true;
		}
		
		if(isVisible)
		{
			
		}
	}
	return false;
}

///---------------------------MatrixPainter-----------------------------
MatrixPainter::MatrixPainter(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height) : Element(pos, size), m_width(width), m_height(height)
{
	matrix = new unsigned char[height*width];
	memset(matrix, 0, height*width);
	
	m_vertices = new sf::VertexArray();
	m_vertices->setPrimitiveType(sf::Quads);
	
	TILE_SIZE = config::initial_zoom;
	
	player_x = 0;
	player_y = 0;
	
	mouse_x = -100;
	mouse_y = -100;
	
	mouse_move = false;
}

MatrixPainter::~MatrixPainter()
{
	m_vertices->clear();
	delete m_vertices;
	delete matrix;
}

unsigned int MatrixPainter::getWidth()
{
	return m_width;
}

unsigned int MatrixPainter::getHeight()
{
	return m_height;
}

unsigned char * & MatrixPainter::getMatrix()
{
	return matrix;
}

void MatrixPainter::setMatrix(unsigned char * other, unsigned int width, unsigned int height)
{
	this->m_width = width;
	this->m_height = height;

	matrix = other;
}

unsigned char & MatrixPainter::getElem(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < m_width && y >= 0 && y < m_height)
		return matrix[y*m_width + x];
	
	return (config::uchar_nil);	
}

void MatrixPainter::setElem(unsigned int x, unsigned int y, unsigned char & elem)
{
	matrix[y*m_width + x] = elem;
}

bool MatrixPainter::onEvent(sf::Event & event)
{
	switch(event.type)
	{
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space)
			{
				player_x = -((float) size.x/2 - m_width*(TILE_SIZE+1)/2);
				player_y = -((float) size.y/2 - m_height*(TILE_SIZE+1)/2);
				prepareToMatrix();
				return true;
			}
		break;
		case sf::Event::MouseWheelMoved:
			if(event.mouseWheel.delta != 0)
			{
				if(TILE_SIZE + event.mouseWheel.delta >= 10 && TILE_SIZE + event.mouseWheel.delta <= 50)
				{
					unsigned int new_zoom = TILE_SIZE + event.mouseWheel.delta;
					unsigned int curr_zoom = TILE_SIZE;
					
					float e_dX = ((float) player_x + mouse_x)/(curr_zoom+1);
					float e_dY = ((float) player_y + mouse_y)/(curr_zoom+1);
					
					float new_x = e_dX*(new_zoom+1) - mouse_x;
					float new_y = e_dY*(new_zoom+1) - mouse_y;
					
					TILE_SIZE = new_zoom;
					player_x = new_x;
					player_y = new_y;
					prepareToMatrix();
				}
			}
			return true;
		break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				mouse_move = true;
				s_move_mouse_x = player_x + event.mouseButton.x;
				s_move_mouse_y = player_y + event.mouseButton.y;
			}
			return true;
		break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				mouse_move = false;
			}
			return true;
		break;
		case sf::Event::MouseMoved:
			if(mouse_move == true)
			{
				player_x = s_move_mouse_x - event.mouseMove.x;
				player_y = s_move_mouse_y - event.mouseMove.y;
				prepareToMatrix();
			}
			mouse_x = event.mouseMove.x;
			mouse_y = event.mouseMove.y;
			return true;
		break;
		default:
		break;
	}
	return false;
}

void MatrixPainter::onResize(sf::Vector2f & new_size)
{
	size = new_size;
	//Console::getConsole().log("onResize with %f %f\n", new_size.x, new_size.y);
}

void MatrixPainter::prepareToMatrix()
{
	//will only draw where is visible!
	begin_x = player_x/(TILE_SIZE+1);
	if(begin_x < 0 || begin_x > size.x)
		begin_x = 0;
	end_x = (size.x+player_x)/(TILE_SIZE+1)+1;
	if(end_x >= m_width)
		end_x = m_width-1;

	begin_y = player_y/(TILE_SIZE+1);
	if(begin_y < 0 || begin_y > size.y)
		begin_y = 0;
	end_y = (size.y+player_y)/(TILE_SIZE+1)+1;
	if(end_y >= m_height)
		end_y = m_height-1;
}

void MatrixPainter::draw(sf::RenderWindow * window)
{
	unsigned int e_X = (player_x + mouse_x)/(TILE_SIZE+1);
	unsigned int e_Y = (player_y + mouse_y)/(TILE_SIZE+1);
	
	m_vertices->clear();
	if((end_x - begin_x + 1 >= m_width) || (end_y - begin_y + 1 >= m_height))
		m_vertices->resize(4);
	else
		m_vertices->resize((end_x - begin_x + 1) * (end_y - begin_y + 1) * 4 + 2 * 4);
	
	//draw area
	sf::Color color = sf::Color(180, 180, 180);
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x-5*(TILE_SIZE+2) - player_x, (float) (TILE_SIZE+1)*begin_y-5*(TILE_SIZE+2) - player_y), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x+TILE_SIZE+5*TILE_SIZE - player_x, (float) (TILE_SIZE+1)*begin_y-5*(TILE_SIZE+2) - player_y), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x+TILE_SIZE+5*TILE_SIZE - player_x, (float) (TILE_SIZE+1)*end_y+TILE_SIZE+5*TILE_SIZE - player_y), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x-5*(TILE_SIZE+2) - player_x, (float) (TILE_SIZE+1)*end_y+TILE_SIZE+5*TILE_SIZE - player_y), color) );
	
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x - player_x -1, 		   (float) (TILE_SIZE+1)*begin_y - player_y -1), sf::Color::Black) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x - player_x, (float) (TILE_SIZE+1)*begin_y - player_y -1), sf::Color::Black) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x - player_x, (float) (TILE_SIZE+1)*end_y - player_y), sf::Color::Black) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x - player_x -1,         (float) (TILE_SIZE+1)*end_y - player_y), sf::Color::Black) );

	//draw the matrix elements
	for(unsigned int i = begin_y; i < end_y; i++)
	{
		for(unsigned int j = begin_x; j < end_x; j++)
		{
			sf::Color color;

			switch(getElem(j, i))
			{
			case 0:
				color = sf::Color::White;
				break;
			case 1:
				color = sf::Color::Red;
				break;
			case 2:
				color = sf::Color::Green;
				break;
			default:
				color = sf::Color::Blue;
				break;
			}
			
			if(e_X == j && e_Y == i)
				color = sf::Color::Yellow;

			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j - player_x, (TILE_SIZE+1)*i - player_y), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE - player_x, (TILE_SIZE+1)*i - player_y), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE - player_x, (TILE_SIZE+1)*i+TILE_SIZE - player_y), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j - player_x, (TILE_SIZE+1)*i+TILE_SIZE - player_y), color) );
		}
	}
	window->draw(*m_vertices);
}

unsigned int MatrixPainter::getTileSize()
{
	return TILE_SIZE;
}

sf::Vector2f & MatrixPainter::getSize()
{
	return size;
}

float MatrixPainter::getPlayerX()
{
	return player_x;
}

float MatrixPainter::getPlayerY()
{
	return player_y;
}

void MatrixPainter::setPlayer(float x, float y)
{
	player_x = x;
	player_y = y;
}
