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

class Screen {
private:
	sf::RenderWindow * window;
	sf::VertexArray * all_rectangles;
public:
	Screen();
	virtual ~Screen();
	void drawObjects(GameMatrix * gm, PlayerState * ps);
	bool isOpen();
};

#endif /* SRC_CLIENT_GRAPHICS_SCREEN_H_ */
