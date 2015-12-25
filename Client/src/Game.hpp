/*
 * Game.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAME_H_
#define SRC_CLIENT_GAME_H_

#include "Console.hpp"
#include "Config.hpp"

#include "InputHandler.hpp"
#include "GameWindow.hpp"
#include "Screen.hpp"

class Game
{
private:
	GameWindow * gm;
	Screen * screen;
	InputHandler * ih;
	//Network * net;
public:
	Game();
	virtual ~Game();
	void run();
};

#endif
