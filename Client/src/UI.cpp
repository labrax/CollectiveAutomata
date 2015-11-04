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
	
	bool EditBox::onEvent(sf::Event & event)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
				case sf::Keyboard::BackSpace:
					//TODO: remover um caracter
					return true;
					break;
				case sf::Keyboard::A:
					txt += 'A';
					return true;
					break;
				case sf::Keyboard::B:
					txt += 'B';
					return true;
					break;
				case sf::Keyboard::C:
					txt += 'C';
					return true;
					break;
				case sf::Keyboard::D:
					txt += 'D';
					return true;
					break;
				case sf::Keyboard::E:
					txt += 'E';
					return true;
					break;
				case sf::Keyboard::F:
					txt += 'F';
					return true;
					break;
				case sf::Keyboard::G:
					txt += 'G';
					return true;
					break;
				case sf::Keyboard::H:
					txt += 'H';
					return true;
					break;
				case sf::Keyboard::I:
					txt += 'I';
					return true;
					break;
				case sf::Keyboard::J:
					txt += 'J';
					return true;
					break;
				case sf::Keyboard::K:
					txt += 'K';
					return true;
					break;
				case sf::Keyboard::L:
					txt += 'L';
					return true;
					break;
				case sf::Keyboard::M:
					txt += 'M';
					return true;
					break;
				case sf::Keyboard::N:
					txt += 'N';
					return true;
					break;
				case sf::Keyboard::O:
					txt += 'O';
					return true;
					break;
				case sf::Keyboard::P:
					txt += 'P';
					return true;
					break;
				case sf::Keyboard::Q:
					txt += 'Q';
					return true;
					break;
				case sf::Keyboard::R:
					txt += 'R';
					return true;
					break;
				case sf::Keyboard::S:
					txt += 'S';
					return true;
					break;
				case sf::Keyboard::T:
					txt += 'T';
					return true;
					break;
				case sf::Keyboard::U:
					txt += 'U';
					return true;
					break;
				case sf::Keyboard::V:
					txt += 'V';
					return true;
					break;
				case sf::Keyboard::W:
					txt += 'W';
					return true;
					break;
				case sf::Keyboard::X:
					txt += 'X';
					return true;
					break;
				case sf::Keyboard::Y:
					txt += 'Y';
					return true;
					break;
				case sf::Keyboard::Z:
					txt += 'Z';
					return true;
					break;

				default:
					break;
			}
		}
		return false;
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
	
	PopUp::~PopUp()
	{
		
	}
	
	void PopUp::draw(sf::RenderWindow * window)
	{
		Console::getConsole().log("dummy draw?\n");
	}
	
	bool PopUp::onEvent(sf::Event & event)
	{
		Console::getConsole().log("dummy event?\n");
		return false;
	}
	
	void PopUp::onResize(sf::Vector2f & new_size)
	{
		size = new_size;
	}
}
