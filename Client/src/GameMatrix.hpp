/*
 * GameMatrix.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAMESTATE_GAMEMATRIX_H_
#define SRC_CLIENT_GAMESTATE_GAMEMATRIX_H_

#include <ctime>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "Config.hpp"

class GameMatrix {
private:
	unsigned int width, height;
	unsigned char * matrix;
	unsigned char * new_matrix;

	unsigned int iteration; //these two will be used to keep in sync with the server
	time_t refTime;

	inline std::vector< std::pair<unsigned char, int> > * getNeighbours(unsigned int x, unsigned int y);
	inline void runIteration();
public:
	GameMatrix(unsigned int width, unsigned int height);
	virtual ~GameMatrix();
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned char * getMatrix();
	unsigned char getElem(unsigned int x, unsigned int y);
	void randomFill();
	void setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t ref_iteration);
	void compute();
};

#endif /* SRC_CLIENT_GAMESTATE_GAMEMATRIX_H_ */
