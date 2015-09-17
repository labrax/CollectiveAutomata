/*
 * Game.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAME_H_
#define SRC_CLIENT_GAME_H_

#include "control/InputHandler.h"
#include "gamestate/GameMatrix.h"
#include "graphics/Screen.h"
#include "gamestate/PlayerState.h"
#include "../common/network/Network.h"

class Game {
private:
	GameMatrix * gm;
	Screen * screen;
	InputHandler * ih;
	PlayerState * ps;
	Network * net;
public:
	Game();
	virtual ~Game();
	void run();
};

#endif /* SRC_CLIENT_GAME_H_ */
