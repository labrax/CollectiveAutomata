/*
 * GraphicsPrimitives.cpp
 *
 *  Created on: 28 de out de 2015
 *      Author: Victor R. Cardoso
 */

#include "GraphicsPrimitives.hpp"

sf::Font gamefont;

void drawText(sf::RenderWindow * window, sf::Vector2f pos, std::string str, size_t size, sf::Color color, enum ALIGNMENT align)
{
	sf::Text text;

	text.setFont(gamefont);
	text.setString(str);
	text.setPosition(pos);
	text.setCharacterSize(size);
	text.setColor(color);
	
	if(align == ALIGN_CENTER)
	{
		pos.x += (text.getLocalBounds().left - text.getLocalBounds().width)/2;
		pos.y += (text.getLocalBounds().top - text.getLocalBounds().height)/2 - size;
		text.setPosition(pos);
	}
	else if(align == ALIGN_RIGHT)
	{
		pos.x = text.getLocalBounds().left - text.getLocalBounds().width + pos.x;
		pos.y = text.getLocalBounds().top - text.getLocalBounds().height + pos.y;
		text.setPosition(pos);
	}
	window->draw(text);
}

void drawRect(sf::RenderWindow * window, sf::Vector2f pos, sf::Vector2f size, sf::Color inside_color, sf::Color border_color)
{
	sf::VertexArray vertices = sf::VertexArray();
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(8);
	
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x-1, pos.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x, pos.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x, pos.y + size.y), border_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x-1, pos.y + size.y), border_color) );
	
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x+1, pos.y+1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x-1, pos.y+1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x + size.x-1, pos.y + size.y-1), inside_color) );
	vertices.append(sf::Vertex ( sf::Vector2f (pos.x+1, pos.y + size.y-1), inside_color) );
	
	window->draw(vertices);
}
