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
#include <cstring>

#include "Config.hpp"

#include "PlayerState.hpp"
#include "UI.hpp"

class GameMatrix : public UI::Window
{
private:
	unsigned int m_width, m_height;
	unsigned char * matrix;
	unsigned char * new_matrix;

	unsigned int iteration; //these two will be used to keep in sync with the server
	time_t refTime;
	
	inline void runIteration();
	
	//to draw
	unsigned int TILE_SIZE;
	unsigned int begin_x, begin_y, end_x, end_y;
	sf::VertexArray * m_vertices;
	unsigned int e_X, e_Y;
	
	float player_x, player_y;
public:
	GameMatrix(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height);
	virtual ~GameMatrix();
	
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned char * & getMatrix();
	
	unsigned int getIteration();

	unsigned char & getElem(unsigned int x, unsigned int y);
	
	void randomFill();
	
	void setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t ref_iteration);
	void compute();
	
	void draw(sf::RenderWindow * window);
	void onEvent(sf::Event event);
	void onResize(sf::Vector2f new_size);
	
	
	void updatePlayerPos(PlayerState * ps);
	void prepareToMatrix(PlayerState * ps);
	void drawMatrix(sf::RenderWindow * window);
};

#endif
