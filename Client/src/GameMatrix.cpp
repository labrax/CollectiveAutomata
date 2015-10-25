/*
 * GameMatrix.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameMatrix.hpp"

GameMatrix::GameMatrix(unsigned int width, unsigned int height) : width(width), height(height)
{
	matrix = new unsigned char[height*width];
	new_matrix = new unsigned char[height*width];
	iteration = 0;
	refTime = time(NULL);
}

GameMatrix::~GameMatrix()
{
	delete matrix;
	delete new_matrix;
}

unsigned int GameMatrix::getWidth()
{
	return width;
}

unsigned int GameMatrix::getHeight()
{
	return height;
}

unsigned char * GameMatrix::getMatrix()
{
	return matrix;
}

unsigned char GameMatrix::getElem(unsigned int x, unsigned int y)
{
	return matrix[y*width + x];
}

void GameMatrix::randomFill()
{
	srand(0);
	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			unsigned char elem = (unsigned char) rand()%2;
			matrix[i*width + j] = elem;
		}
	}
}

void GameMatrix::setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t refTime)
{
	this->width = width;
	this->height = height;

	delete(matrix);
	matrix = new unsigned char[height*width];

	for(unsigned int i = 0; i < height*width; i++)
	{
		matrix[i] = other[i];
	}

	this->iteration = iteration;
	this->refTime = refTime;
}

bool comp(const std::pair<unsigned char, int> & a, const std::pair<unsigned char, int> & b)
{
	if(a.second >= b.second)
		return true;
	return false;
}

std::vector< std::pair<unsigned char, int> > * GameMatrix::getNeighbours(unsigned int x, unsigned int y)
{
	std::vector< std::pair <unsigned char, int> > * neighbours = new std::vector< std::pair <unsigned char, int> >();
	for(int i = (int)y-1; i <= (int)y+1; i++)
	{
		for(int j = (int)x-1; j <= (int)x+1; j++)
		{
			if(i == (int)y && j == (int)x)
				continue;
			if(i < 0 || i >= (int) height || j < 0 || j >= (int) width)
				continue;

			std::vector< std::pair <unsigned char, int> >::iterator it;
			for(it = neighbours->begin(); it != neighbours->end(); it++)
			{
				if((*it).first == matrix[i*width + j])
				{
					(*it).second++;
					break;
				}
			}

			if(it == neighbours->end())
			{
				neighbours->insert(neighbours->end(), std::pair<unsigned char, int>(matrix[i*width + j], 1));
			}

		}
	}
	//ordena pelo segundo
	std::sort(neighbours->begin(), neighbours->end(), comp);

	return neighbours;
}

void GameMatrix::runIteration()
{
	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			std::vector< std::pair<unsigned char, int> > * neighbours = getNeighbours(j, i);

			unsigned int amount_life = 0;

			for(unsigned int k = 0; k < neighbours->size(); k++)
			{
				if( (*neighbours)[k].first != 0 )
					amount_life += (*neighbours)[k].second;
				//printf("%c: %d\n", (*neighbours)[k].first + '0', (*neighbours)[k].second);
			}

			//printf("amount_life: %d\n", amount_life);

			unsigned char next_element = 0;
			if((*neighbours)[0].first == 0)
			{
				if(neighbours->size() > 1)
					next_element = (*neighbours)[1].first;
			}

			if(matrix[i*width + j] == 0) //se estava morto
			{
				if(amount_life == 3) //e tem 3, fica vivo do tipo que tem mais:
					new_matrix[i*width + j] = next_element;
				else
					new_matrix[i*width + j] = 0;
			}
			else //se estava vivo
			{
				if(amount_life >= 2 && amount_life <= 3) //continua vivo com o que tinha antes
					new_matrix[i*width + j] = matrix[i*width + j]; //outra opção é: (*neighbours)[0].first //quem teve mais participação mantém
				else //morre
					new_matrix[i*width + j] = 0;
			}

			delete(neighbours);
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
