/*
 * Config.cpp
 *
 *  Created on: 15 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Config.hpp"

namespace config
{
	//game
	sf::Time time_per_frame = sf::seconds(1.0f/frameratelimit);

	//gamestate
	unsigned int height = 450, width = 800, iterations_per_sec = 1;

	//player
	unsigned int initial_zoom = 4;

	//screen
	unsigned int frameratelimit = 50, screen_height = 600, screen_width = 800;
}
