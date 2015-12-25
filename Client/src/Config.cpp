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
	unsigned int height = 30, width = 40, iterations_per_sec = 1;
	unsigned char uchar_nil = 0;

	//player
	unsigned int initial_zoom = 10;

	//screen
	unsigned int frameratelimit = 50, screen_height = 600, screen_width = 800;
	
	//player console
	sf::Color color_inside(32, 32, 32, 128);
	sf::Color color_border(192, 192, 192, 128);
	sf::Color color_text(32, 32, 200);
	
	unsigned int txt_size = 15;
}
