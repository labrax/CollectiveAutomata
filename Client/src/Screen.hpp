/*
 * Screen.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_GRAPHICS_SCREEN_H_
#define SRC_CLIENT_GRAPHICS_SCREEN_H_

#include <cassert>
#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "PlayerState.hpp"
#include "GameMatrix.hpp"
#include "Config.hpp"
#include "Console.hpp"

class Screen {
private:
	//window variables
	sf::RenderWindow * window;
	unsigned int width, height;
	
	//matrix renderer
	sf::VertexArray * m_vertices;
	int moved_x, moved_y;
	
	unsigned int TILE_SIZE;
	unsigned int begin_x, begin_y, end_x, end_y;
	
	//pause rendering
	bool paused;
	
	sf::Font gamefont;
public:
	Screen();
	virtual ~Screen();
	
	sf::RenderWindow * getWindow();
	unsigned int getWidth();
	unsigned int getHeight();
	
	void stopDraw();
	void resumeDraw();
	
	void draw(GameMatrix * gm, PlayerState * ps);
	void prepareToMatrix(GameMatrix * gm, PlayerState * ps);
	void drawMatrix(GameMatrix * gm, PlayerState * ps);
	
	void updateViewCenter(float dx, float dy);
	void updateScreenSize(unsigned int width, unsigned int height);
	
	void drawText(sf::Vector2f pos, std::string str, size_t size, sf::Color color, bool center = false);
	void drawRect(sf::Vector2f pos, sf::Vector2f size, sf::Color inside_color, sf::Color border_color);
};

#include "UI.hpp"

#endif /* SRC_CLIENT_GRAPHICS_SCREEN_H_ */
