/*
 * UI.cpp
 *
 *  Created on: 28 de out de 2015
 *      Author: Victor R. Cardoso
 */

#include "UI.hpp"

namespace UI
{
	Manager::Manager()
	{
		
	}
	Manager::~Manager()
	{
		
	}
	Manager & Manager::getManager()
	{
		static Manager * instance = new Manager();
		return *instance;
	}
	Screen * Manager::getScreen()
	{
		return screen;
	}
	void Manager::setScreen(Screen * screen)
	{
		this->screen = screen;
	}
	
	Window::Window(sf::Vector2f pos, sf::Vector2f size, std::string name) : Element(pos, size), name(name)
	{
		
	}
	Window::~Window()
	{
		
	}
	
	void Window::draw()
	{
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		Manager::getManager().getScreen()->drawText(sf::Vector2f(pos.x+3, pos.y-3), name, 15, sf::Color(255,255,255));
		
		for(size_t i = 0; i < elements.size(); i++)
		{
			if(elements[i]->pos.x + elements[i]->size.x > this->pos.x + this->size.x)
			{
				elements[i]->size.x = this->size.x + this->pos.x - elements[i]->pos.x;
			}
			elements[i]->draw();
		}
	}
	
	Element::Element(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size)
	{
		
	}
	Element::~Element()
	{
		
	}

	Label::Label(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt)
	{
		
	}
	
	void Label::draw()
	{
		Manager::getManager().getScreen()->drawText(sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
	
	EditBox::EditBox(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt)
	{
		
	}
	
	void EditBox::draw()
	{
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		Manager::getManager().getScreen()->drawText(sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
	
	CheckBox::CheckBox(sf::Vector2f pos, sf::Vector2f size, bool state) : Element(pos, size), state(state)
	{
		
	}
			
	void CheckBox::draw()
	{
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		if(state == true)
			Manager::getManager().getScreen()->drawText(sf::Vector2f(pos.x+3, pos.y-3), "X", size.y, sf::Color(255,255,255));
	}
	
	Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt), state(false)
	{
		
	}
			
	void Button::draw()
	{
		if(state == false)
		{
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		}
		else
		{
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(0,0,0));
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(192,192,192));
			Manager::getManager().getScreen()->drawRect(pos, sf::Vector2f(size.x, size.y), sf::Color(0,0,0), sf::Color(192,192,192));
		}
		Manager::getManager().getScreen()->drawText(sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
}
