/*
 * PlayerState.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "PlayerState.hpp"

PlayerState::PlayerState() : tileZoom(config::initial_zoom), dx(0), dy(0), mouse_x(-100), mouse_y(-100), exit(false), moved(true), center(false), state(STATE_LOGO)
{
	player_console = PlayerConsole();
	player_console.isVisible = false;
}

PlayerState::~PlayerState()
{

}

void PlayerState::setTileZoom(unsigned int zoom)
{
	if(tileZoom != zoom)
		moved = true;
	tileZoom = zoom;
}

unsigned int PlayerState::getTileZoom()
{
	return tileZoom;
}

void PlayerState::setPos(float dx, float dy)
{
	if(this->dx != dx || this->dy != dy)
		moved = true;
	this->dx = dx;
	this->dy = dy;
	//Console::getConsole().log("%f %f\n", dx, dy);
}

float PlayerState::getPosX()
{
	return dx;
}

float PlayerState::getPosY()
{
	return dy;
}

void PlayerState::setExit()
{
	this->exit = true;
}

bool PlayerState::isExit()
{
	return exit;
}

bool PlayerState::isMoved()
{
	if(moved == true)
	{
		moved = false;
		return true;
	}
	return moved;
}

void PlayerState::setMouse(long x, long y)
{
	this->mouse_x = x;
	this->mouse_y = y;
}

long PlayerState::getMouseX()
{
	return mouse_x;
}

long PlayerState::getMouseY()
{
	return mouse_y;
}

void PlayerState::setCenter()
{
	center = true;
}

bool PlayerState::getCenter()
{
	if(center == true)
	{
		center = false;
		return true;
	}
	return false;
}

enum GameState PlayerState::getState()
{
	return state;
}

void PlayerState::setState(enum GameState state)
{
	this->state = state;
}

PlayerConsole & PlayerState::getPlayerConsole()
{
	return player_console;
}



PlayerConsole::PlayerConsole() : UI::Element(sf::Vector2f(0, 0), sf::Vector2f(0, 0))
{
	
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

void PlayerConsole::onEvent(sf::Event event)
{
	
}

void PlayerConsole::onResize(sf::Vector2f new_size)
{
	size = new_size;
}
