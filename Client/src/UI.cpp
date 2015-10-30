/*
 * UI.cpp
 *
 *  Created on: 28 de out de 2015
 *      Author: Victor R. Cardoso
 */

#include "UI.hpp"

namespace UI
{
	/*Manager::Manager()
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
	sf::RenderWindow * Manager::getWindow()
	{
		return window;
	}
	void Manager::setWindow(sf::RenderWindow * window)
	{
		this->window = window;
	}*/
	
	Element::Element(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size), parent(NULL), isVisible(true)
	{
		
	}
	Element::~Element()
	{
		
	}
	
	Window::Window(sf::Vector2f pos, sf::Vector2f size, std::string name) : Element(pos, size), name(name)
	{
		
	}
	Window::~Window()
	{
		for(size_t i = 0; i < elements.size(); i++)
		{
			delete(elements[i]);
		}
	}
	
	void Window::addElement(Element * element, bool horizontal_spacing, bool vertical_spacing)
	{
		//Console::getConsole().log("Window has %lu elements!\n", elements.size());
		
		if(elements.size() == 0)
		{
			elements.insert(elements.end(), element);
		}
		else
		{
			if(horizontal_spacing == true)
				element->pos.x = elements[elements.size()-1]->pos.x + elements[elements.size()-1]->size.x + 10;
			else
				element->pos.x = elements[elements.size()-1]->pos.x;
				
			if(vertical_spacing == true)
				element->pos.y = elements[elements.size()-1]->pos.y + elements[elements.size()-1]->size.y + 10;
			else
				element->pos.y = elements[elements.size()-1]->pos.y;
			elements.insert(elements.end(), element);
		}
	}
	
	void Window::draw(sf::RenderWindow * window)
	{
		drawRect(window, pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		drawRect(window, pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		drawRect(window, pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		if(name != "")
			drawText(window, sf::Vector2f(pos.x+3, pos.y-3), name, 15, sf::Color(255,255,255));
	}
	
	void Window::drawElements(sf::RenderWindow * window)
	{
		for(size_t i = 0; i < elements.size(); i++)
		{
			elements[i]->draw(window);
		}
	}
	
	bool Window::onEvent(sf::Event & event)
	{
		for(size_t i = 0; i < elements.size(); i++)
		{
			if(elements[i]->onEvent(event) == true)
				return true;
		}
		return false;
	}
	
	void Window::onResize(sf::Vector2f & new_size)
	{
		//Console::getConsole().log("amount: %lu\n", elements.size());
		//Console::getConsole().log("%f %f\n", new_size.x, new_size.y);
		for(size_t i = 0; i < elements.size(); i++)
		{
			elements[i]->onResize(new_size);
			//Console::getConsole().log("%f %f\n", elements[i]->size.x, elements[i]->size.y);
		}
		
		size = new_size;
	}

	Label::Label(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt)
	{
		
	}
	
	void Label::draw(sf::RenderWindow * window)
	{
		drawText(window, sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
	
	EditBox::EditBox(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt)
	{
		
	}
	
	void EditBox::draw(sf::RenderWindow * window)
	{
		drawRect(window, pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		drawRect(window, pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		drawRect(window, pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		drawText(window, sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
	
	CheckBox::CheckBox(sf::Vector2f pos, sf::Vector2f size, bool state) : Element(pos, size), state(state)
	{
		
	}
			
	void CheckBox::draw(sf::RenderWindow * window)
	{
		drawRect(window, pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
		drawRect(window, pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
		drawRect(window, pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		if(state == true)
			drawText(window, sf::Vector2f(pos.x+3, pos.y-3), "X", size.y, sf::Color(255,255,255));
	}
	
	Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string txt) : Element(pos, size), txt(txt), state(false)
	{
		
	}
			
	void Button::draw(sf::RenderWindow * window)
	{
		if(state == false)
		{
			drawRect(window, pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(192,192,192));
			drawRect(window, pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(224,224,224));
			drawRect(window, pos, sf::Vector2f(size.x, size.y), sf::Color(32,32,32), sf::Color(192,192,192));
		}
		else
		{
			drawRect(window, pos, sf::Vector2f(size.x+2, size.y+2), sf::Color::Black, sf::Color(0,0,0));
			drawRect(window, pos, sf::Vector2f(size.x+1, size.y+1), sf::Color::Black, sf::Color(192,192,192));
			drawRect(window, pos, sf::Vector2f(size.x, size.y), sf::Color(0,0,0), sf::Color(192,192,192));
		}
		drawText(window, sf::Vector2f(pos.x+3, pos.y-3), txt, size.y, sf::Color(255,255,255));
	}
	
	PopUp::PopUp(sf::Vector2f pos, sf::Vector2f size, std::string name) : Window(pos,size, name)
	{
		answer = false;
		isVisible = false;
	}
	
	void PopUp::draw(sf::RenderWindow * window)
	{
		if(isVisible)
		{
			drawRect(window, pos, size, sf::Color(255,255,255,127), sf::Color(255,255,255,127));
			drawText(window, sf::Vector2f(size.x/2, size.y/2), "Exit? Y/N", 40, sf::Color::Blue, ALIGN_CENTER);
		}
	}
	
	bool PopUp::onEvent(sf::Event & event)
	{
		if(isVisible)
		{
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Y)
				{
					answer = true;
					return true;
				}
				else if(event.key.code == sf::Keyboard::N)
				{
					answer = false;
					isVisible = false;
					return true;
				}
			}
		}
		return false;
	}
	
	void PopUp::onResize(sf::Vector2f & new_size)
	{
		size = new_size;
	}
}
