/*
 * PlayerState.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_
#define SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_

class PlayerState {
private:
	unsigned int tileZoom;
	long dx, dy;
public:
	PlayerState();
	virtual ~PlayerState();
	void setTileZoom(unsigned int zoom);
	unsigned int getTileZoom();
	void setPos(unsigned int dx, unsigned int dy);
	long getPosX();
	long getPosY();
};

#endif /* SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_ */
