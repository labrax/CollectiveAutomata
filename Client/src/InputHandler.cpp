/*
 * InputHandler.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "InputHandler.hpp"

InputHandler::InputHandler()
{
	
}

InputHandler::~InputHandler()
{

}

void InputHandler::poolEvents(Screen * screen)
{
	sf::RenderWindow * window = screen->getWindow();

	sf::Event event;
	while (window->pollEvent(event))
	{
		if(event.type == sf::Event::Resized)
		{
			sf::Vector2f size(event.size.width, event.size.height);
			screen->onResize(size);
		}
		else
			screen->onEvent(event);
		
		//if (event.type == sf::Event::Closed) //TODO
		//	ps->setExit();
	}
}
