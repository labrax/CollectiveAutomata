/*
 * Game.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "../common/Config.h"
#include "Game.h"

Game::Game() {
	gm = new GameMatrix(config::width, config::height);
	gm->randomFill();
	screen = new Screen();
	ih = new InputHandler();
	ps = new PlayerState();
	net = new Network();
}

Game::~Game() {
	delete(ih);
	delete(screen);
	delete(gm);
	delete(ps);
	delete(net);
}

void Game::run() {
	bool isRunning = true;
	while(isRunning) {
		//network
		//gamematrix
		gm->compute();
		//input
		//screen
		screen->drawObjects(gm, ps);
		if(screen->isOpen() == false)
			isRunning = false;
	}
}

