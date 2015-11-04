/*
 * GAMEUI.hpp
 *
 *  Created on: 30 de out de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef GAMEUI_CONFIG_H_
#define GAMEUI_CONFIG_H_

#include "UI.hpp"
#include "Config.hpp"

#include <string>
#include <vector>

class PlayerConsoleInput : public UI::EditBox
{
	public:
		PlayerConsoleInput(sf::Vector2f pos, sf::Vector2f size, std::string txt);
		
		void onResize(sf::Vector2f & new_size);
};

class PlayerConsole : public UI::Element
{
public:
	PlayerConsoleInput eb;
	std::vector<std::string> str;
	PlayerConsole();
	~PlayerConsole();
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
	void onResize(sf::Vector2f & new_size);
};

class ClosePopUp : public UI::PopUp
{
	public:
		ClosePopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
		
		void draw(sf::RenderWindow * window);
		bool onEvent(sf::Event & event);
};

class BeginPopUp : public UI::PopUp
{
	public:
		BeginPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
		
		void draw(sf::RenderWindow * window);
		bool onEvent(sf::Event & event);
};

#endif
