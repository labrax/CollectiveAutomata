/*
 * Screen.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Screen.h"
#include "../../common/Config.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cstdio>

Screen::Screen() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	window = new sf::RenderWindow(sf::VideoMode(config::screen_width, config::screen_height), "SFML works!");
	window->setFramerateLimit(config::frameratelimit);
	window->setPosition(sf::Vector2i((desktop.width - config::screen_width)/2, (desktop.height - config::screen_height)/2)); //center screen

	all_rectangles = new sf::VertexArray(sf::Quads);
}

Screen::~Screen() {
	delete(all_rectangles);
	delete(window);
}

void Screen::drawObjects(GameMatrix * gm, PlayerState * ps) {
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	window->clear();

	//all_rectangles->clear();

	unsigned int TILE_SIZE = 4; //pegar do jogador
	sf::RectangleShape white_rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	white_rectangle.setFillColor(sf::Color::White);

	sf::RectangleShape cyan_rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	cyan_rectangle.setFillColor(sf::Color::Cyan);
	for(unsigned int i = 0; i < gm->getHeight(); i++)
	{
		for(unsigned int j = 0; j < gm->getWidth(); j++)
		{
			if(gm->getElem(j, i) == 1)
			{
				cyan_rectangle.setPosition(sf::Vector2f((TILE_SIZE+1)*i+1, (TILE_SIZE+1)*j+1));
				window->draw(cyan_rectangle);
				//all_rectangles->append( sf::Vertex( sf::Vector2f( (TILE_SIZE+1)*i+1, (TILE_SIZE+1)*j+1), sf::Color::Red ) );
			}
			else
			{
				white_rectangle.setPosition(sf::Vector2f((TILE_SIZE+1)*i+1, (TILE_SIZE+1)*j+1));
				window->draw(white_rectangle);
				//all_rectangles->append( sf::Vertex( sf::Vector2f( (TILE_SIZE+1)*i+1, (TILE_SIZE+1)*j+1), sf::Color::White ) );
			}
		}
	}
	//window->draw(all_rectangles);

	window->display();
}

bool Screen::isOpen()
{
	return window->isOpen();
}
