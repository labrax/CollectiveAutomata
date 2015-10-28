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
#include "GameMatrix.hpp"
#include "Screen.hpp"
#include "PlayerState.hpp"

class Game
{
private:
	GameMatrix * gm;
	Screen * screen;
	InputHandler * ih;
	PlayerState * ps;
	//Network * net;
public:
	Game();
	virtual ~Game();
	void run();
};

#endif
