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

enum GameState
{
	STATE_LOGO,
	STATE_MENU,
	STATE_PLAYING,
	STATE_END
};

class PlayerState {
private:
	unsigned int tileZoom;
	float dx, dy;
	long mouse_x, mouse_y;

	bool exit, moved, center;
	
	enum GameState state;
public:
	PlayerState();
	virtual ~PlayerState();
	
	void setTileZoom(unsigned int zoom);
	unsigned int getTileZoom();
	
	void setPos(float dx, float dy);
	float getPosX();
	float getPosY();
	
	void setExit();
	bool isExit();
	
	bool isMoved();
	
	void setMouse(long x, long y);
	long getMouseX();
	long getMouseY();
	
	void setCenter();
	bool getCenter();
	
	enum GameState getState();
	void setState(enum GameState state);
};

#endif /* SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_ */
