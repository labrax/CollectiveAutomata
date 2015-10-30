/*
 * PlayerState.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "PlayerState.hpp"

PlayerConsole::PlayerConsole() : UI::Element(sf::Vector2f(0, 0), sf::Vector2f(0, 0))
{
	isVisible = false;
}

PlayerConsole::~PlayerConsole()
{
	
}

void PlayerConsole::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, config::color_inside, config::color_border);
	}
}

bool PlayerConsole::onEvent(sf::Event & event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::BackSlash || event.key.code == sf::Keyboard::Equal)
		{
			isVisible = (!isVisible);
			return true;
		}
	}
	return false;
}

void PlayerConsole::onResize(sf::Vector2f & new_size)
{
	size.x = new_size.x;
	size.y = new_size.y/3;
}
