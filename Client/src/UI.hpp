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
#include "Console.hpp"

#define DEFAULT_MIN_DISTANCE 30
#define DEFAULT_CHECKBOX_SIZE 20
#define DEFAULT_BUTTON_SIZE_X 50
#define DEFAULT_BUTTON_SIZE_Y 20
#define DEFAULT_LABEL_WIDTH 300
#define DEFAULT_LABEL_HEIGHT 20

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
			
			void addElement(Element *, bool horizontal_spacing, bool vertical_spacing);
			
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
