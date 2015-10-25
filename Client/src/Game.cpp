/*
 * Game.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Game.hpp"

Game::Game() {
	gm = new GameMatrix(config::width, config::height);
	gm->randomFill();
	screen = new Screen();
	ps = new PlayerState();
	ih = new InputHandler(ps);
	//net = new Network();
}

Game::~Game() {
	delete(ih);
	delete(screen);
	delete(gm);
	delete(ps);
	//delete(net);
}

void Game::run() {
	bool isRunning = true;
	screen->prepareScreen(gm, ps);

	sf::Clock clock;
	while(isRunning) {
		//network
		//gamematrix
		gm->compute();
		//input
		ih->poolEvents(screen);
		if(ps->isMoved())
		{
			screen->updateViewCenter(ps->getPosX(), ps->getPosY());
		}
		//screen
		screen->drawObjects(gm, ps);
		if(ps->isExit())
			isRunning = false;

		sf::Time elapsedTime = clock.restart();
		if(elapsedTime < config::time_per_frame)
		{
			sf::sleep(config::time_per_frame - elapsedTime); //TODO: corrigir com o fps
		}
	}
}

