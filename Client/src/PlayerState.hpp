/*
 * PlayerState.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_
#define SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_

#include "Config.hpp"
#include "Console.hpp"

#include "UI.hpp"

#include <string>
#include <vector>

enum GameState
{
	STATE_LOGO,
	//STATE_MENU,
	STATE_PLAYING,
	STATE_END
};

class PlayerConsole : public UI::Element
{
public:
	std::vector<std::string> str;
	PlayerConsole();
	~PlayerConsole();
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
	void onResize(sf::Vector2f & new_size);
};

#endif
