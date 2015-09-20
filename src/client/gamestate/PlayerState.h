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
	int dx, dy;

	bool exit, moved;
public:
	PlayerState();
	virtual ~PlayerState();
	void setTileZoom(unsigned int zoom);
	unsigned int getTileZoom();
	void setPos(int dx, int dy);
	long getPosX();
	long getPosY();
	void setExit();
	bool isExit();
	bool isMoved();
};

#endif /* SRC_CLIENT_GAMESTATE_PLAYERSTATE_H_ */
