/*
 * UI.hpp
 *
 *  Created on: 28 de out de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef UI_CONFIG_H_
#define UI_CONFIG_H_

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "Screen.hpp"

namespace UI
{
	class Manager
	{
		private:
			Screen * screen;
		protected:
			Manager();
		public:
			~Manager();
			static Manager & getManager();
			
			Screen * getScreen();
			void setScreen(Screen * screen);
	};
	
	class Element
	{
		public:
			sf::Vector2f pos, size;
			Element(sf::Vector2f pos, sf::Vector2f size);
			virtual ~Element();
			
			virtual void draw() = 0;
	};
	
	class Window : public Element
	{
		public:
			std::string name;
			std::vector<Element *> elements;
			Window(sf::Vector2f pos, sf::Vector2f size, std::string name);
			virtual ~Window();
			
			void draw();
	};
	
	class Label : public Element
	{
		public:
			std::string txt;
			Label(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw();
	};
	
	class EditBox : public Element
	{
		public:
			std::string txt;
			EditBox(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw();		
	};
	
	class CheckBox : public Element
	{
		public:
			bool state;
			CheckBox(sf::Vector2f pos, sf::Vector2f size, bool state);
			
			void draw();
	};
	
	class Button : public Element
	{
		public:
			std::string txt;
			bool state;
			Button(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw();
	};
	
};

#endif
