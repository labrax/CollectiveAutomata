/*
 * Screen.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Screen.hpp"

Screen::Screen()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	window = new sf::RenderWindow(sf::VideoMode(1, 1), "CollectiveAutomata!");
	updateScreenSize(config::screen_width, config::screen_height);

	window->setFramerateLimit(config::frameratelimit);
	window->setVerticalSyncEnabled(true);
	window->setPosition(sf::Vector2i((desktop.width - width)/2, (desktop.height - height)/2)); //center screen
	window->setKeyRepeatEnabled(false);

	m_vertices = new sf::VertexArray();
	m_vertices->setPrimitiveType(sf::Quads);

	paused = false;
	
	if(!gamefont.loadFromFile("04B_03__.TTF"))
	{
		Console::getConsole().log("Erro carregando fonte! Arquivo: \"%s\"\n", "04B_03__.TTF");
		assert(false);
	}
}

Screen::~Screen()
{
	window->close();
	delete(m_vertices);
	delete(window);
}
sf::RenderWindow *  Screen::getWindow()
{
	return window;
}

unsigned int Screen::getWidth()
{
	return width;
}

unsigned int Screen::getHeight()
{
	return height;
}

void Screen::stopDraw()
{
	paused = true;
}

void Screen::resumeDraw()
{
	paused = false;
}

void Screen::draw(GameMatrix * gm, PlayerState * ps)
{
	//if(paused == true)
	//	return;
	
	window->clear();
	
	switch(ps->getState())
	{
		case STATE_PLAYING:
		{
			if(ps->isMoved())
			{
				updateViewCenter(ps->getPosX(), ps->getPosY());
				prepareToMatrix(gm, ps);
			}
			drawMatrix(gm, ps);
			drawText(sf::Vector2f(ps->getPosX(), ps->getPosY()), "Hello World!", 25, sf::Color::Red);
			break;
		}
		case STATE_LOGO:
		{
			updateViewCenter(0, 0);
			//drawText(sf::Vector2f(width/2, height/2), "CollectiveAutomata", 50, sf::Color::Blue, true);
			
			/**TESTING**/
			UI::Manager::getManager().setScreen(this);
			UI::Window window(sf::Vector2f(50, 50), sf::Vector2f(500, 400), "UserInformation");
			UI::Label label1(sf::Vector2f(100, 150), sf::Vector2f(300, 20), "<user>");
			UI::EditBox editbox1(sf::Vector2f(100, 180), sf::Vector2f(300, 20), "<huehuehue>");
			UI::CheckBox checkbox1(sf::Vector2f(100, 210), sf::Vector2f(20, 20), true);
			UI::CheckBox checkbox2(sf::Vector2f(130, 210), sf::Vector2f(20, 20), false);
			UI::Button button(sf::Vector2f(160, 210), sf::Vector2f(50, 20), "Click");
			UI::Button button2(sf::Vector2f(220, 210), sf::Vector2f(50, 20), "Click");
			button2.state = true;
			window.elements.insert(window.elements.end(), &label1);
			window.elements.insert(window.elements.end(), &editbox1);
			window.elements.insert(window.elements.end(), &checkbox1);
			window.elements.insert(window.elements.end(), &checkbox2);
			window.elements.insert(window.elements.end(), &button);
			window.elements.insert(window.elements.end(), &button2);
			//label1.draw();
			window.draw();
			/**TESTING**/
			break;
		}
		case STATE_MENU:
		{
			updateViewCenter(0, 0);
			drawText(sf::Vector2f(width/2, height/2), "Menu", 50, sf::Color::Red, true);
			break;
		}
		case STATE_END:
		{
			updateViewCenter(0, 0);
			drawText(sf::Vector2f(width/2, height/2), "gg!", 50, sf::Color::Blue, true);
			break;
		}
		default:
		{
			break;
		}
	}
	
	window->display();
}

void Screen::prepareToMatrix(GameMatrix * gm, PlayerState * ps)
{
	TILE_SIZE = ps->getTileZoom(); //pegar do jogador
	
	//will only draw where is visible!
	begin_x = moved_x/(TILE_SIZE+1);
	if(begin_x < 0 || begin_x > width)
		begin_x = 0;
	end_x = (width+moved_x)/(TILE_SIZE+1)+1;
	if(end_x >= gm->getWidth())
		end_x = gm->getWidth()-1;

	begin_y = moved_y/(TILE_SIZE+1);
	if(begin_y < 0 || begin_y > height)
		begin_y = 0;
	end_y = (height+moved_y)/(TILE_SIZE+1)+1;
	if(end_y >= gm->getHeight())
		end_y = gm->getHeight()-1;
}

void Screen::drawMatrix(GameMatrix * gm, PlayerState * ps)
{
	m_vertices->clear();
	if((end_x - begin_x + 1 >= gm->getWidth()) || (end_y - begin_y + 1 >= gm->getHeight()))
		m_vertices->resize(4);
	else
		m_vertices->resize((end_x - begin_x + 1) * (end_y - begin_y + 1) * 4 * 2 + 4);
	
	unsigned int e_X = (moved_x+ps->getMouseX())/(TILE_SIZE+1);
	unsigned int e_Y = (moved_y+ps->getMouseY())/(TILE_SIZE+1);
	
	//draw area
	sf::Color color = sf::Color(180, 180, 180);
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x-5*(TILE_SIZE+2), (float) (TILE_SIZE+1)*begin_y-5*(TILE_SIZE+2)), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x+TILE_SIZE+5*TILE_SIZE, (float) (TILE_SIZE+1)*begin_y-5*(TILE_SIZE+2)), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*end_x+TILE_SIZE+5*TILE_SIZE, (float) (TILE_SIZE+1)*end_y+TILE_SIZE+5*TILE_SIZE), color) );
	m_vertices->append(sf::Vertex ( sf::Vector2f ((float)(TILE_SIZE+1)*begin_x-5*(TILE_SIZE+2), (float) (TILE_SIZE+1)*end_y+TILE_SIZE+5*TILE_SIZE), color) );

	//draw the matrix elements
	for(unsigned int i = begin_y; i < end_y; i++)
	{
		for(unsigned int j = begin_x; j < end_x; j++)
		{
			sf::Color color;

			switch(gm->getElem(j, i))
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

			m_vertices->append(sf::Vertex ( sf::Vector2f ((float) (TILE_SIZE+1)*j - 1, (float) (TILE_SIZE+1)*i - 1), sf::Color::Black) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE+1, (float) (TILE_SIZE+1)*i - 1), sf::Color::Black) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE+1, (TILE_SIZE+1)*i+TILE_SIZE+1), sf::Color::Black) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((float) (TILE_SIZE+1)*j - 1, (TILE_SIZE+1)*i+TILE_SIZE+1), sf::Color::Black) );

			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j, (TILE_SIZE+1)*i), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE, (TILE_SIZE+1)*i), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE, (TILE_SIZE+1)*i+TILE_SIZE), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j, (TILE_SIZE+1)*i+TILE_SIZE), color) );
		}
	}
	window->draw(*m_vertices);
}

void Screen::updateViewCenter(float dx, float dy)
{
	moved_x = (int) dx;
	moved_y = (int) dy;
	
	sf::View view = window->getView();
	view.setCenter((float) width/2 + dx, (float) height/2 + dy);
	window->setView(view);
}

void Screen::updateScreenSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	if(window->getSize().x != width && window->getSize().y != height)
		window->setSize(sf::Vector2<unsigned int>(width, height));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::View new_view = sf::View(sf::Vector2f( (desktop.width-width)/2, (desktop.height - height/2)/2 ), sf::Vector2f(width, height));
	new_view.setCenter((float) width/2, (float) height/2);
	window->setView( new_view );
}

void Screen::drawText(sf::Vector2f pos, std::string str, size_t size, sf::Color color, bool center)
{
	sf::Text text;

	text.setFont(gamefont);

	text.setString(str);
	
	text.setPosition(pos);

	text.setCharacterSize(size);

	text.setColor(color);
	
	if(center == true)
	{
		pos.x += (text.getLocalBounds().left - text.getLocalBounds().width)/2;
		pos.y += (text.getLocalBounds().top - text.getLocalBounds().height)/2 - size;
		text.setPosition(pos);
	}
	
	window->draw(text);
}

void Screen::drawRect(sf::Vector2f pos, sf::Vector2f size, sf::Color inside_color, sf::Color border_color)
{
	sf::VertexArray vertices = sf::VertexArray();
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(8);
	
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x-1, pos.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x, pos.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x, pos.y + size.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x-1, pos.y + size.y), border_color) );
	
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x+1, pos.y+1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x-1, pos.y+1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x-1, pos.y + size.y-1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x+1, pos.y + size.y-1), inside_color) );
	
	window->draw(vertices);
}

