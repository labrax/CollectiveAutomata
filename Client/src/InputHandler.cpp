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
		{
			float e_dX = ((float) ps->getPosX() + screen->getWidth()/2)/(ps->getTileZoom()+1);
			float e_dY = ((float) ps->getPosY() + screen->getHeight()/2)/(ps->getTileZoom()+1);
			
			screen->updateScreenSize(event.size.width, event.size.height);
			
			float new_x = e_dX*(ps->getTileZoom()+1) - screen->getWidth()/2;
			float new_y = e_dY*(ps->getTileZoom()+1) - screen->getHeight()/2;
			
			ps->setPos(new_x, new_y);
			//ps->setPos(ps->getPosX(), ps->getPosY());
		}
		else if (event.type == sf::Event::LostFocus)
		    screen->stopDraw();
		else if (event.type == sf::Event::GainedFocus)
		    screen->resumeDraw();
		else if (event.type == sf::Event::KeyPressed)
		{
		    /*if (event.key.code == sf::Keyboard::Escape)
		    {
		    	
		        //std::cout << "the escape key was pressed" << std::endl;
		        //std::cout << "control:" << event.key.control << std::endl;
		        //std::cout << "alt:" << event.key.alt << std::endl;
		        //std::cout << "shift:" << event.key.shift << std::endl;
		        //std::cout << "system:" << event.key.system << std::endl;
		        
		        switch(ps->getState())
				{
					case STATE_END:
					{
						ps->setExit();
						break;
					}
					default:
					{
						ps->setState(STATE_END);
						break;
					}
				}
		    }
		    else*/ if(event.key.code == sf::Keyboard::Space)
		    {
				ps->setCenter();
			}
			else if(event.key.code == sf::Keyboard::Return)
			{
				switch(ps->getState())
				{
					case STATE_LOGO:
					{
						ps->setState(STATE_PLAYING);
						break;
					}
					default:
					{
						break;
					}
				}
			}
			else if(event.key.code == sf::Keyboard::BackSlash || event.key.code == sf::Keyboard::Q)
			{
				ps->getPlayerConsole().isVisible = (!ps->getPlayerConsole().isVisible);
			}
		}
		else if (event.type == sf::Event::MouseWheelMoved)
		{
			if(event.mouseWheel.delta != 0)
			{
				if(ps->getTileZoom() + event.mouseWheel.delta >= 10 && ps->getTileZoom() + event.mouseWheel.delta <= 50)
				{
					unsigned int new_zoom = ps->getTileZoom() + event.mouseWheel.delta;
					unsigned int curr_zoom = ps->getTileZoom();
					
					float e_dX = ((float) ps->getPosX() + ps->getMouseX())/(curr_zoom+1);
					float e_dY = ((float) ps->getPosY() + ps->getMouseY())/(curr_zoom+1);
					
					float new_x = e_dX*(new_zoom+1) - ps->getMouseX();
					float new_y = e_dY*(new_zoom+1) - ps->getMouseY();
					
					ps->setTileZoom(new_zoom);
					ps->setPos(new_x, new_y);
				}
			}
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
