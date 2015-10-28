/*
 * Config.hpp
 *
 *  Created on: 15 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_

#include <SFML/System/Time.hpp>

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics.hpp>

namespace config {
	//game
	extern sf::Time time_per_frame;
	//gamestate
	extern unsigned int height, width, iterations_per_sec;
	//player
	extern unsigned int initial_zoom;
	//screen
	extern unsigned int frameratelimit, screen_height, screen_width;
	//player console
	extern sf::Color color_inside, color_border, color_text;
}

#endif
