/*
 * GameMatrix.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameMatrix.h"

#include "../../common/Config.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

GameMatrix::GameMatrix(unsigned int width, unsigned int height) : width(width), height(height)
{
	matrix = new unsigned char[height*width];
	iteration = 0;
	refTime = time(NULL);
}

GameMatrix::~GameMatrix()
{
	delete matrix;
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
	return matrix[y*height + x];
}

void GameMatrix::randomFill()
{
	srand(time(NULL));
	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			unsigned char elem = (unsigned char) rand()%2;
			matrix[i*height + j] = elem;
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
	unsigned char * new_matrix = new unsigned char[width*height];
	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			/*TODO: rule*/
			if(matrix[i*height + j] == 0)
				new_matrix[i*height + j] = 1;
			else
				new_matrix[i*height + j] = 0;
			/*TODO: rule*/
		}
	}

	unsigned char * temp = matrix; //replace the old with the new one
	matrix = new_matrix;
	delete(temp);
}

void GameMatrix::compute()
{
	return;
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
