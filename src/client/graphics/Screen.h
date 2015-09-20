/*
 * Screen.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GRAPHICS_SCREEN_H_
#define SRC_CLIENT_GRAPHICS_SCREEN_H_

#include "../gamestate/PlayerState.h"
#include "../gamestate/GameMatrix.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Screen {
private:
	sf::RenderWindow * window;
	sf::VertexArray * m_vertices;
	unsigned int width, height;
	bool paused;
public:
	Screen();
	virtual ~Screen();
	void prepareScreen(GameMatrix * gm, PlayerState * ps);
	void drawObjects(GameMatrix * gm, PlayerState * ps);
	void updateViewCenter(int dx, int dy);
	void updateScreenSize(unsigned int width, unsigned int height, int dx, int dy);
	sf::RenderWindow * getWindow();
	void stopDraw();
	void resumeDraw();
};

#endif /* SRC_CLIENT_GRAPHICS_SCREEN_H_ */
