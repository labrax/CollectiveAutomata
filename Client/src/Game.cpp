/*
 * Game.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Game.hpp"

Game::Game() {
	gm = new GameMatrix(sf::Vector2f(0, 0), sf::Vector2f(0, 0), config::width, config::height);
	gm->randomFill();
	screen = new Screen(gm);
	
	ps = new PlayerState();
	ps->setCenter();
	
	gm->addElement(&(ps->getPlayerConsole()), false, false);
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

	sf::Clock clock;
	while(isRunning) {
		//network
		//gamematrix
		gm->compute();
		//input
		ih->poolEvents(screen);
		
		/*exchange messages*/
		if(ps->getCenter())
		{
			ps->setPos(-((float) screen->getWidth()/2 - gm->getWidth()*(ps->getTileZoom()+1)/2), -((float) screen->getHeight()/2-gm->getHeight()*(ps->getTileZoom()+1)/2));
		}
		
		if(ps->isMoved())
		{
			gm->prepareToMatrix(ps);
		}
		gm->updatePlayerPos(ps);
		/*exchange messages*/
		
		//screen
		screen->draw(gm, ps);
		
		if(ps->isExit())
			isRunning = false;

		sf::Time elapsedTime = clock.restart();
		if(elapsedTime < config::time_per_frame)
		{
			sf::sleep(config::time_per_frame - elapsedTime); //TODO: corrigir com o fps
		}
	}
}

