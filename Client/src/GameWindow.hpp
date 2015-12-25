/*
 * GameWindow.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAMESTATE_GameWindow_H_
#define SRC_CLIENT_GAMESTATE_GameWindow_H_

#include <ctime>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "Config.hpp"

#include "UI.hpp"
#include "GameUI.hpp"

class GameWindow : public UI::Window
{
private:
	MatrixPainter matrix;
	unsigned char * next_matrix;

	unsigned int iteration; //these two will be used to keep in sync with the server
	time_t refTime;
	
	inline void runIteration();
	
	bool next_matrix_valid;
	//exit popup
	UI::PopUp * popup;
public:
	GameWindow(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height);
	virtual ~GameWindow();
	
	unsigned int getIteration();
	
	void randomFill();
	
	void setMatrix(unsigned char * other, unsigned int width, unsigned int height, unsigned int iteration, time_t ref_iteration);
	void compute();
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
	void onResize(sf::Vector2f & new_size);
	
	bool exit();
};

#endif
