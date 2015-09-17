/*
 * PlayerState.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "PlayerState.h"
#include "../../common/Config.h"

PlayerState::PlayerState()
{
	tileZoom = config::initial_zoom;
	dx = 0;
	dy = 0;
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

void PlayerState::setPos(unsigned int dx, unsigned int dy)
{
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
