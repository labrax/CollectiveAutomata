/*
 * PlayerState.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "PlayerState.hpp"

PlayerState::PlayerState()
{
	tileZoom = config::initial_zoom;
	dx = 0;
	dy = 0;
	exit = false;
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

void PlayerState::setPos(int dx, int dy)
{
	if(this->dx != dx || this->dy != dy)
		moved = true;
	this->dx = dx;
	this->dy = dy;
}

long PlayerState::getPosX()
{
	return dx;
}

long PlayerState::getPosY()
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
