/*
 * Screen.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Screen.hpp"

Screen::Screen(UI::Element * drawable) : drawable(drawable)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	window = new sf::RenderWindow(sf::VideoMode(1, 1), "CollectiveAutomata!");
	
	sf::Vector2f new_size = sf::Vector2f(config::screen_width, config::screen_height);
	onResize(new_size);

	window->setFramerateLimit(config::frameratelimit);
	window->setVerticalSyncEnabled(true);
	window->setPosition(sf::Vector2i((desktop.width - width)/2, (desktop.height - height)/2)); //center screen
	window->setKeyRepeatEnabled(false);

	paused = false;
	
	if(!gamefont.loadFromFile("04B_03__.TTF"))
	{
		Console::getConsole().log("Erro carregando fonte! Arquivo: \"%s\"\n", "04B_03__.TTF");
		assert(false);
	}
	
	//UI::Manager::getManager().setWindow(window);
}

Screen::~Screen()
{
	window->close();
	delete(window);
}
sf::RenderWindow *  Screen::getWindow()
{
	return window;
}

unsigned int Screen::getWidth()
{
	return width;
}

unsigned int Screen::getHeight()
{
	return height;
}

void Screen::stopDraw()
{
	paused = true;
}

void Screen::resumeDraw()
{
	paused = false;
}

void Screen::draw(GameMatrix * gm)
{
	window->clear();
	//if(paused == true)
	//	return;
	
	gm->draw(window);
		
	window->display();
	return;
	
	drawText(window, sf::Vector2f(width/2, height/2), "CollectiveAutomata", 50, sf::Color::Blue, ALIGN_CENTER);
			/*
			UI::Window window(sf::Vector2f(width/2 - 500/2, height/2 - 400/2), sf::Vector2f(500, 400), "Menu");
			
			UI::Element * element = new UI::Label(sf::Vector2f(window.pos.x+50, window.pos.y+50), sf::Vector2f(DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT), "Player name:");
			window.addElement(element, false, false);
			element = new UI::EditBox(sf::Vector2f(0, 0), sf::Vector2f(DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT), "");
			window.addElement(element, false, true);
			element = new UI::CheckBox(sf::Vector2f(0, 0), sf::Vector2f(DEFAULT_CHECKBOX_SIZE, DEFAULT_CHECKBOX_SIZE), true);
			window.addElement(element, false, true);
			element = new UI::CheckBox(sf::Vector2f(0, 0), sf::Vector2f(DEFAULT_CHECKBOX_SIZE, DEFAULT_CHECKBOX_SIZE), false);
			window.addElement(element, true, false);
			element = new UI::Button(sf::Vector2f(0, 0), sf::Vector2f(DEFAULT_BUTTON_SIZE_X, DEFAULT_BUTTON_SIZE_Y), "Go!");
			window.addElement(element, true, false);
			element= new UI::Button(sf::Vector2f(0, 0), sf::Vector2f(DEFAULT_BUTTON_SIZE_X, DEFAULT_BUTTON_SIZE_Y), "Click");
			((UI::Button *) element)->state = true;
			window.addElement(element, true, false);
			window.draw(this->window);
			*/
	drawText(window, sf::Vector2f(width/2, height/2), "gg!", 50, sf::Color::Blue, ALIGN_CENTER);

	window->display();
}

void Screen::onEvent(sf::Event & event)
{
	if (event.type == sf::Event::LostFocus)
		stopDraw();
	else if (event.type == sf::Event::GainedFocus)
		resumeDraw();
	else
		drawable->onEvent(event);
}

void Screen::onResize(sf::Vector2f & new_size)
{
	this->width = new_size.x;
	this->height = new_size.y;

	if(window->getSize().x != width && window->getSize().y != height)
		window->setSize(sf::Vector2<unsigned int>(width, height));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::View new_view = sf::View(sf::Vector2f( (desktop.width-width)/2, (desktop.height - height/2)/2 ), sf::Vector2f(width, height));
	new_view.setCenter((float) width/2, (float) height/2);
	window->setView( new_view );
	
	sf::Vector2f passed_size = sf::Vector2f(width, height);
	drawable->onResize(passed_size);
}
