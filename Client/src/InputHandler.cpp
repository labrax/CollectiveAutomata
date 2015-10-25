/*
 * InputHandler.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "InputHandler.hpp"

InputHandler::InputHandler(PlayerState * ps) : ps(ps)
{
	mouse_move = false;
}

InputHandler::~InputHandler()
{

}

void InputHandler::poolEvents(Screen * screen)
{
	sf::RenderWindow * window = screen->getWindow();

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			ps->setExit();
		else if (event.type == sf::Event::Resized)
			screen->updateScreenSize(event.size.width, event.size.height, ps->getPosX(), ps->getPosY());
		else if (event.type == sf::Event::LostFocus)
		    screen->stopDraw();
		else if (event.type == sf::Event::GainedFocus)
		    screen->resumeDraw();
		else if (event.type == sf::Event::KeyPressed)
		{
		    if (event.key.code == sf::Keyboard::Escape)
		    {
		    	/*
		        std::cout << "the escape key was pressed" << std::endl;
		        std::cout << "control:" << event.key.control << std::endl;
		        std::cout << "alt:" << event.key.alt << std::endl;
		        std::cout << "shift:" << event.key.shift << std::endl;
		        std::cout << "system:" << event.key.system << std::endl;
		        */
		    }
		}
		else if (event.type == sf::Event::MouseWheelMoved)
		{
			if(event.mouseWheel.delta < 0)
			{
				if(ps->getTileZoom() + event.mouseWheel.delta >= 5)
				{
					unsigned int curr_zoom = ps->getTileZoom();
					ps->setTileZoom(curr_zoom + event.mouseWheel.delta);
				}
			}
			else
			{
				if(ps->getTileZoom() + event.mouseWheel.delta <= 50)
				{
					unsigned int curr_zoom = ps->getTileZoom();
					ps->setTileZoom(curr_zoom + event.mouseWheel.delta);
				}
			}

			//screen->getWindow()->getSize().x/2;
			//screen->getWindow()->getSize().y/2;

		    /*std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
		    std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
		    std::cout << "mouse y: " << event.mouseWheel.y << std::endl;*/
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
		    if (event.mouseButton.button == sf::Mouse::Right)
		    {
		    	mouse_move = true;
		    	mouse_x = ps->getPosX() + event.mouseButton.x;
		    	mouse_y = ps->getPosY() + event.mouseButton.y;
		    }
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
		    if (event.mouseButton.button == sf::Mouse::Right)
		    {
		    	mouse_move = false;
		    }
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			if(mouse_move == true)
			{
				//int screen_X = screen->getWindow()->getSize().x;
				//int screen_Y = screen->getWindow()->getSize().y;

				ps->setPos(mouse_x - event.mouseMove.x, mouse_y - event.mouseMove.y);
			}
			ps->setMouse(event.mouseMove.x, event.mouseMove.y);
		}
	}

}
