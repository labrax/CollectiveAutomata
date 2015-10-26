/*
 * PlayerState.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "PlayerState.hpp"

PlayerState::PlayerState() : tileZoom(config::initial_zoom), dx(0), dy(0), mouse_x(-100), mouse_y(-100), exit(false)
{
	
}

PlayerState::~PlayerState()
{

}

void PlayerState::setTileZoom(unsigned int zoom)
{
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
