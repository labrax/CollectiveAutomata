/*
 * GameWindow.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameWindow.hpp"

GameWindow::GameWindow(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height) : Window(pos, size, ""), matrix(pos, size, width, height), iteration(0)
{
	refTime = time(NULL);
	
	next_matrix = NULL;
	next_matrix_valid = false;

	addElement(new BeginPopUp(pos, size, ""), false, false);
	
	popup = new ClosePopUp(pos, size, "");
	addElement(popup, false, false);
	
//	addElement(&matrix, false, false);
}

GameWindow::~GameWindow()
{
	if(next_matrix != NULL)
		delete(next_matrix);
}

unsigned int GameWindow::getIteration()
{
	return iteration;
}

void GameWindow::randomFill()
{
	unsigned int m_height = matrix.getHeight();
	unsigned int m_width = matrix.getWidth();
	srand(1337);
	for(unsigned int i = 0; i < m_height; i++)
	{
		for(unsigned int j = 0; j < m_width; j++)
		{
			unsigned char elem = (unsigned char) rand()%2;
			matrix.setElem(j, i, elem);
		}
	}
}

void GameWindow::setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t refTime)
{
	delete matrix.getMatrix();
	matrix.setMatrix(other, width, height);

	next_matrix_valid = false;

	this->iteration = iteration;
	this->refTime = refTime;
}

void GameWindow::runIteration()
{
	unsigned int m_height = matrix.getHeight();
	unsigned int m_width = matrix.getWidth();
	unsigned char * curr_matrix = matrix.getMatrix();
	
	if(next_matrix_valid == false)
	{
		next_matrix = new unsigned char[m_height*m_width];
		memset(next_matrix, 0, m_height*m_width);
		next_matrix_valid = true;
	}
//#pragma omp parallel for
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

					unsigned char e = (curr_matrix)[k*m_width + l];
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

			if(curr_matrix[i*m_width + j] == 0) //se estava morto
			{
				if(amount_life == 3) //e tem 3, fica vivo do tipo que tem mais:
					next_matrix[i*m_width + j] = next_element;
				else
					next_matrix[i*m_width + j] = 0;
			}
			else //se estava vivo
			{
				if(amount_life >= 2 && amount_life <= 3) //continua vivo com o que tinha antes
					next_matrix[i*m_width + j] = curr_matrix[i*m_width + j];
				else //morre
					next_matrix[i*m_width + j] = 0;
			}
		}
	}

	matrix.setMatrix(next_matrix, m_width, m_height); //swaps matrix
	next_matrix = curr_matrix;
}

void GameWindow::compute()
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

void GameWindow::draw(sf::RenderWindow * window)
{	
	Window::draw(window);
	//TODO: check drawing order
	
	matrix.draw(window);
	
	char iteration[16];
	sprintf(iteration, "Iteration: %u", getIteration());
	drawText(window, sf::Vector2f(size.x, 0), std::string(iteration), 25, sf::Color::Blue, ALIGN_RIGHT);
	
	drawElements(window);
}

bool GameWindow::onEvent(sf::Event & event)
{
	//Console::getConsole().log("player_: %f %f\n", player_x, player_y);
	//Console::getConsole().log("mouse_: %u %u\n", mouse_x, mouse_y);
	if(Window::onEvent(event) == true) //check if any element returned before
		return true;
	
	if(matrix.onEvent(event) == true)
		return true;
	
	if(event.type == sf::Event::Closed)
	{
		popup->isVisible = true;
		return true;
	}
	return false;
	//return false;
}

void GameWindow::onResize(sf::Vector2f & new_size)
{
	sf::Vector2f size = matrix.getSize();
	float player_x = matrix.getPlayerX();
	float player_y = matrix.getPlayerY();
	unsigned int m_height = matrix.getHeight();
	unsigned int m_width = matrix.getWidth();
	unsigned int TILE_SIZE = matrix.getTileSize();
	
	if(matrix.size.x == 0 && matrix.size.y == 0)
	{
		Window::onResize(new_size);
		
		matrix.setPlayer(-((float) new_size.x/2 - m_width*(TILE_SIZE+1)/2), -((float) new_size.y/2 - m_height*(TILE_SIZE+1)/2));
	}
	else
	{
		float e_dX = ((float) player_x + size.x/2)/(TILE_SIZE + 1);
		float e_dY = ((float) player_y + size.y/2)/(TILE_SIZE + 1);

		Window::onResize(new_size);

		matrix.setPlayer(((float) e_dX)*(TILE_SIZE + 1) - new_size.x/2, ((float) e_dY)*(TILE_SIZE + 1) - new_size.y/2);
	}
	
	matrix.onResize(new_size);
	matrix.prepareToMatrix();
}

bool GameWindow::exit()
{
	if(popup->isVisible && popup->answer)
		return true;
	return false;
}
