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
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

#include "GraphicsPrimitives.hpp"
#include "Console.hpp"

#define DEFAULT_MIN_DISTANCE 30
#define DEFAULT_CHECKBOX_SIZE 20
#define DEFAULT_BUTTON_SIZE_X 50
#define DEFAULT_BUTTON_SIZE_Y 20
#define DEFAULT_LABEL_WIDTH 300
#define DEFAULT_LABEL_HEIGHT 20

namespace UI
{
	enum ELEMENT_TYPE
	{
		DRAWABLE,
		ELEMENT,
		WINDOW,
		LABEL,
		CHECKBOX,
		BUTTON,
		POPUP
	};
	
	class Drawable
	{
	public:
		virtual void draw(sf::RenderWindow * window) = 0;
	};
	
	/*class Manager
	{
		private:
			sf::RenderWindow * window;
			sf::Font * gamefont;
		protected:
			Manager();
		public:
			~Manager();
			static Manager & getManager();
			
			sf::RenderWindow * getWindow();
			void setWindow(sf::RenderWindow * window);
	};*/
	
	class Element : public Drawable
	{
		public:
			sf::Vector2f pos, size;
			Element * parent;
			bool isVisible;
			
			Element(sf::Vector2f pos, sf::Vector2f size);
			virtual ~Element();
			
			virtual bool onEvent(sf::Event & event) = 0;
			virtual void onResize(sf::Vector2f & new_size) = 0;
	};
	
	class Window : public Element
	{
		public:
			std::string name;
			std::vector<Element *> elements;
			Window(sf::Vector2f pos, sf::Vector2f size, std::string name);
			virtual ~Window();
			
			void addElement(Element *, bool horizontal_spacing, bool vertical_spacing);
			
			void draw(sf::RenderWindow * window);
			void drawElements(sf::RenderWindow * window);
			
			bool onEvent(sf::Event & event);
			void onResize(sf::Vector2f & new_size);
	};
	
	class Label : public Element
	{
		public:
			std::string txt;
			Label(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw(sf::RenderWindow * window);
	};
	
	class EditBox : public Element
	{
		public:
			std::string txt;
			EditBox(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw(sf::RenderWindow * window);
	};
	
	class CheckBox : public Element
	{
		public:
			bool state;
			CheckBox(sf::Vector2f pos, sf::Vector2f size, bool state);
			
			void draw(sf::RenderWindow * window);
	};
	
	class Button : public Element
	{
		public:
			std::string txt;
			bool state;
			Button(sf::Vector2f pos, sf::Vector2f size, std::string txt);
			
			void draw(sf::RenderWindow * window);
	};
	
	class PopUp : public Window
	{
		public:
			bool answer;
			
			PopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
			
			void draw(sf::RenderWindow * window) ;
			bool onEvent(sf::Event & event);
			void onResize(sf::Vector2f & new_size);
	};
};

#endif
