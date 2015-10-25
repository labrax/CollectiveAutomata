/*
 * GameMatrix.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameMatrix.hpp"

GameMatrix::GameMatrix(unsigned int width, unsigned int height) : width(width), height(height), iteration(0)
{
	matrix = new unsigned char[height*width];
	new_matrix = new unsigned char[height*width];
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

unsigned char * & GameMatrix::getMatrix()
{
	return matrix;
}

inline unsigned char & GameMatrix::getElem(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < width && y >= 0 && y < height)
		return matrix[y*width + x];
	
	unsigned char nil = 0;
	return nil;
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

void GameMatrix::runIteration()
{
#pragma omp parallel for
	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
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
					new_matrix[i*width + j] = matrix[i*width + j];
				else //morre
					new_matrix[i*width + j] = 0;
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
