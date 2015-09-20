/*
 * Config.cpp
 *
 *  Created on: 15 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Config.h"
#include <SFML/System/Time.hpp>

namespace config
{
	//game
	sf::Time time_per_frame = sf::seconds(1.0f/frameratelimit);

	//gamestate
	unsigned int height = 120, width = 160, iterations_per_sec = 1;

	//player
	unsigned int initial_zoom = 4;

	//screen
	unsigned int frameratelimit = 50, screen_height = 600, screen_width = 800;
}
