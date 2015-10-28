/*
 * GraphicsPrimitives.hpp
 *
 *  Created on: 28 de out de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef GRAHICSPRIMITIVES_CONFIG_H_
#define GRAHICSPRIMITIVES_CONFIG_H_

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics.hpp>

enum ALIGNMENT
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

void drawText(sf::RenderWindow * window, sf::Vector2f pos, std::string str, size_t size, sf::Color color, enum ALIGNMENT = ALIGN_LEFT);
void drawRect(sf::RenderWindow * window, sf::Vector2f pos, sf::Vector2f size, sf::Color inside_color, sf::Color border_color);

extern sf::Font gamefont;

#endif
