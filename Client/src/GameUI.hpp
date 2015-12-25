/*
 * GAMEUI.hpp
 *
 *  Created on: 30 de out de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef GAMEUI_CONFIG_H_
#define GAMEUI_CONFIG_H_

#include "UI.hpp"
#include "Config.hpp"
#include "GraphicsPrimitives.hpp"

#include "Console.hpp"

#include <cstring>

#include <string>
#include <vector>

class PlayerConsoleInput : public UI::EditBox
{
public:
	PlayerConsoleInput(sf::Vector2f pos, sf::Vector2f size, std::string txt);
	
	void onResize(sf::Vector2f & new_size);
};

class PlayerConsole : public UI::Element
{
public:
	PlayerConsoleInput eb;
	std::vector<std::string> str;
	PlayerConsole();
	~PlayerConsole();
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
	void onResize(sf::Vector2f & new_size);
};

class ClosePopUp : public UI::PopUp
{
public:
	ClosePopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
};

class BeginPopUp : public UI::PopUp
{
public:
	BeginPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
};

class EditorPopUp : public UI::PopUp
{
public:
	size_t amountElements;
	EditorPopUp(sf::Vector2f pos, sf::Vector2f size, std::string name);
	
	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
};

class MatrixPainter : public UI::Element
{
private:
	//matrix information
	unsigned int m_width, m_height;
	unsigned char * matrix;

	//to draw
	unsigned int TILE_SIZE;
	unsigned int begin_x, begin_y, end_x, end_y;
	sf::VertexArray * m_vertices;

	//indicate screen dragging
	float player_x, player_y;
	
	//indicate mouse reference
	bool mouse_move;
	long mouse_x, mouse_y;
	long s_move_mouse_x, s_move_mouse_y;
public:
	MatrixPainter(sf::Vector2f pos, sf::Vector2f size, unsigned int width, unsigned int height);
	~MatrixPainter();
	
	void prepareToMatrix();

	void draw(sf::RenderWindow * window);
	bool onEvent(sf::Event & event);
	void onResize(sf::Vector2f & new_size);
	
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned char * & getMatrix();
	
	//ATTENTION: this doesn't delete the previous one! and only replaces pointer!
	void setMatrix(unsigned char * other, unsigned int width, unsigned int height);
	
	unsigned char & getElem(unsigned int x, unsigned int y);
	void setElem(unsigned int x, unsigned int y, unsigned char & elem);
	
	unsigned int getTileSize();
	sf::Vector2f & getSize();
	float getPlayerX();
	float getPlayerY();
	void setPlayer(float x, float y);
};

#endif
