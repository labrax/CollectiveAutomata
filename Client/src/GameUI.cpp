/*
 * GAMEUI.cpp
 *
 *  Created on: 30 de out de 2015
 *      Author: Victor R. Cardoso
 */

#include "GameUI.hpp"

PlayerConsoleInput::PlayerConsoleInput(sf::Vector2f pos, sf::Vector2f size, std::string txt) : EditBox(pos, size, txt)
{
	
}

void PlayerConsoleInput::onResize(sf::Vector2f & new_size)
{
	size.x = new_size.x;
}

PlayerConsole::PlayerConsole() : UI::Element(sf::Vector2f(0, 0), sf::Vector2f(0, 0)), eb(PlayerConsoleInput(sf::Vector2f(0, size.y - DEFAULT_LABEL_WIDTH), sf::Vector2f(size.x, DEFAULT_LABEL_WIDTH), ""))
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


ClosePopUp::ClosePopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : PopUp(pos,size, name)
{

}

void ClosePopUp::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, sf::Color(255,255,255,127), sf::Color(255,255,255,127));
		drawText(window, sf::Vector2f(size.x/2, size.y/2), "Exit? Y/N", 40, sf::Color::Blue, ALIGN_CENTER);
	}
}

bool ClosePopUp::onEvent(sf::Event & event)
{
	if(isVisible)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Y)
			{
				answer = true;
				return true;
			}
			else if(event.key.code == sf::Keyboard::N)
			{
				answer = false;
				isVisible = false;
				return true;
			}
		}
	}
	return false;
}

BeginPopUp::BeginPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : UI::PopUp(pos, size, name)
{
	isVisible = true;
}

void BeginPopUp::draw(sf::RenderWindow * window)
{
	if(isVisible)
	{
		drawRect(window, pos, size, sf::Color::Black, sf::Color::Black);
		drawText(window, sf::Vector2f(size.x/2, size.y/2), "CollectiveAutomata", 50, sf::Color::Blue, ALIGN_CENTER);
	}
}

bool BeginPopUp::onEvent(sf::Event & event)
{
	if(isVisible)
	{
		if(event.type  ==  sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
			{
				isVisible = false;
				return true;
			}
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			if( (event.mouseButton.x >= pos.x && event.mouseButton.x < pos.x + size.x) && (event.mouseButton.y >= pos.y && event.mouseButton.y < pos.y + size.y) )
			{
				isVisible = false;
				return true;
			}
		}
	}
	return false;
}
