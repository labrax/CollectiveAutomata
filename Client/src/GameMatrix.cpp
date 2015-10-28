/*
 * GameMatrix.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameMatrix.hpp"

GameMatrix::GameMatrix(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height) : Window(pos, size, ""), m_width(width), m_height(height), iteration(0)
{
	matrix = new unsigned char[height*width];
	new_matrix = new unsigned char[height*width];
	refTime = time(NULL);
	
	m_vertices = new sf::VertexArray();
	m_vertices->setPrimitiveType(sf::Quads);
}

GameMatrix::~GameMatrix()
{
	delete(m_vertices);
	delete matrix;
	delete new_matrix;
}

unsigned int GameMatrix::getWidth()
{
	return m_width;
}

unsigned int GameMatrix::getHeight()
{
	return m_height;
}

unsigned char * & GameMatrix::getMatrix()
{
	return matrix;
}

unsigned int GameMatrix::getIteration()
{
	return iteration;
}

inline unsigned char & GameMatrix::getElem(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < m_width && y >= 0 && y < m_height)
		return matrix[y*m_width + x];
	
	return (config::uchar_nil);
}

void GameMatrix::randomFill()
{
	srand(1337);
	for(unsigned int i = 0; i < m_height; i++)
	{
		for(unsigned int j = 0; j < m_width; j++)
		{
			unsigned char elem = (unsigned char) rand()%2;
			matrix[i*m_width + j] = elem;
		}
	}
}

void GameMatrix::setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t refTime)
{
	this->m_width = width;
	this->m_height = height;

	delete(matrix);
	matrix = new unsigned char[height*width];

	for(unsigned int i = 0; i < height*width; i++)
	{
		matrix[i] = other[i];
	}

	this->iteration = iteration;
	this->refTime = refTime;
}

void GameMatrix::runIteration()
{
#pragma omp parallel for
	for(unsigned int i = 0; i < m_height; i++)
	{
		for(unsigned int j = 0; j < m_width; j++)
		{
			int amount_each[256];
			memset(amount_each, 0, sizeof(int) * 256);
			int amount_max = 0;
			int index_max = 0;
			
			int amount_life = 0;
			
			for(unsigned int k = i-1; k <= i+1; k++)
			{
				for(unsigned int l = j-1; l <= j+1; l++)
				{
					if(k == i && l == j)
						continue;

					unsigned char e = getElem(l, k);
					amount_each[e]++;
					
					if(e > 0)
					{
						if(amount_each[e] > amount_max)
						{
							amount_max = amount_each[e];
							index_max = e;
						}
						amount_life++;
					}
				}
			}
			
			unsigned char next_element = index_max;

			if(matrix[i*m_width + j] == 0) //se estava morto
			{
				if(amount_life == 3) //e tem 3, fica vivo do tipo que tem mais:
					new_matrix[i*m_width + j] = next_element;
				else
					new_matrix[i*m_width + j] = 0;
			}
			else //se estava vivo
			{
				if(amount_life >= 2 && amount_life <= 3) //continua vivo com o que tinha antes
					new_matrix[i*m_width + j] = matrix[i*m_width + j];
				else //morre
					new_matrix[i*m_width + j] = 0;
			}
		}
	}

	unsigned char * temp = matrix; //replace the old with the new one
	matrix = new_matrix;
	new_matrix = temp;
}

void GameMatrix::compute()
{
	time_t currTime = time(NULL);
	unsigned int currIteration = floor((currTime - refTime)/config::iterations_per_sec);
	if(currIteration > iteration )
	{
		for(unsigned int i = iteration; i < currIteration; i++)
		{
			runIteration();
		}
		iteration = currIteration;
	}
}

void GameMatrix::draw(sf::RenderWindow * window)
{
	Window::draw(window);
	drawMatrix(window);
	
	char iteration[16];
	sprintf(iteration, "Iteration: %u", getIteration());
	drawText(window, sf::Vector2f(size.x, 0), std::string(iteration), 25, sf::Color::Blue, ALIGN_RIGHT);
}

void GameMatrix::onEvent(sf::Event event)
{
	
}

void GameMatrix::onResize(sf::Vector2f new_size)
{
	Window::onResize(new_size);
}

void GameMatrix::prepareToMatrix(PlayerState * ps)
{
	TILE_SIZE = ps->getTileZoom(); //pegar do jogador
	
	player_x = ps->getPosX();
	player_y = ps->getPosY();
	
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
		
	e_X = (player_x+ps->getMouseX())/(TILE_SIZE+1);
	e_Y = (player_y+ps->getMouseY())/(TILE_SIZE+1);
}

void GameMatrix::updatePlayerPos(PlayerState * ps)
{
	e_X = (player_x+ps->getMouseX())/(TILE_SIZE+1);
	e_Y = (player_y+ps->getMouseY())/(TILE_SIZE+1);
}

void GameMatrix::drawMatrix(sf::RenderWindow * window)
{
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
