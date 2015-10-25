/*
 * Screen.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Screen.hpp"

Screen::Screen()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	window = new sf::RenderWindow(sf::VideoMode(1, 1), "CollectiveAutomata!");
	updateScreenSize(config::screen_width, config::screen_height, 0, 0);

	window->setFramerateLimit(config::frameratelimit);
	window->setVerticalSyncEnabled(true);
	window->setPosition(sf::Vector2i((desktop.width - width)/2, (desktop.height - height)/2)); //center screen
	window->setKeyRepeatEnabled(false);

	m_vertices = new sf::VertexArray();
	m_vertices->setPrimitiveType(sf::Quads);

	paused = false;

	//glEnable(GL_TEXTURE_2D);
	//glOrtho(0.0f, (double)config::screen_width, (double)config::screen_height, 0.0f, 0.0f, 1.0f);
}

Screen::~Screen()
{
	window->close();
	delete(m_vertices);
	delete(window);
}

//TODO: não funciona
void Screen::prepareScreen(GameMatrix * gm, PlayerState * ps)
{
	unsigned int TILE_SIZE = ps->getTileZoom();
	m_vertices->resize(gm->getWidth() * gm->getHeight() * 4);
	for(unsigned int i = 0; i < gm->getHeight(); i++)
	{
		for(unsigned int j = 0; j < gm->getWidth(); j++)
		{
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*i, (TILE_SIZE+1)*j), sf::Color::Red) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*i, (TILE_SIZE+1)*j+TILE_SIZE), sf::Color::Red) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j+TILE_SIZE), sf::Color::Red) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j), sf::Color::Red) );
		}
	}
}

void Screen::drawObjects(GameMatrix * gm, PlayerState * ps)
{
	//if(paused == true)
	//	return;

	window->clear();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//m_vertices.clear();
	m_vertices->resize(gm->getWidth() * gm->getHeight() * 4);

	unsigned int TILE_SIZE = ps->getTileZoom(); //pegar do jogador

	for(unsigned int i = 0; i < gm->getHeight(); i++)
	{
		for(unsigned int j = 0; j < gm->getWidth(); j++)
		{
			sf::Color color;

			switch(gm->getElem(j, i))
			{
			case 0:
				color = sf::Color::White;
				//glColor3b(255, 255, 255);
				break;
			case 1:
				//glColor3b(255, 0, 0);
				color = sf::Color::Red;
				break;
			case 2:
				//glColor3b(0, 255, 0);
				color = sf::Color::Green;
				break;
			default:
				//glColor3b(0, 0, 255);
				color = sf::Color::Blue;
				break;
			}

			/*unsigned int index = i*j*4;
			if(m_vertices[index].color != color)
			{
				m_vertices[index].color = color;
				m_vertices[index].position = sf::Vector2f ((TILE_SIZE+1)*i, (TILE_SIZE+1)*j);
				m_vertices[index].texCoords = sf::Vector2f (0, 0);
				m_vertices[index+1].color = color;
				m_vertices[index+1].position = sf::Vector2f ((TILE_SIZE+1)*i, (TILE_SIZE+1)*j+TILE_SIZE);
				m_vertices[index+1].texCoords = sf::Vector2f (0, 0);
				m_vertices[index+2].color = color;
				m_vertices[index+2].position = sf::Vector2f ((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j+TILE_SIZE);
				m_vertices[index+2].texCoords = sf::Vector2f (0, 0);
				m_vertices[index+3].color = color;
				m_vertices[index+3].position = sf::Vector2f ((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j);
				m_vertices[index+3].texCoords = sf::Vector2f (0, 0);
			}*/

			/*glBegin(GL_QUADS);
			glColor3b(0, 0, 255);
			glVertex2i((TILE_SIZE+1)*i, (TILE_SIZE+1)*j);
			glVertex2i((TILE_SIZE+1)*i, (TILE_SIZE+1)*j+TILE_SIZE);
			glVertex2i((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j+TILE_SIZE);
			glVertex2i((TILE_SIZE+1)*i+TILE_SIZE, (TILE_SIZE+1)*j);
			glEnd();*/

			/*glBegin(GL_QUADS);
			glColor3b(0,0,255);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glVertex2f(1.0f, 1.0f);
			glVertex2f(0.0f, 1.0f);
			glEnd();*/

			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j, (TILE_SIZE+1)*i), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE, (TILE_SIZE+1)*i), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j+TILE_SIZE, (TILE_SIZE+1)*i+TILE_SIZE), color) );
			m_vertices->append(sf::Vertex ( sf::Vector2f ((TILE_SIZE+1)*j, (TILE_SIZE+1)*i+TILE_SIZE), color) );
		}
	}

	window->draw(*m_vertices);

	window->display();
}

void Screen::updateViewCenter(int dx, int dy)
{
	sf::View view = window->getView();
	view.setCenter((float) width/2 + dx, (float) height/2 + dy);
	window->setView(view);
}

void Screen::updateScreenSize(unsigned int width, unsigned int height, int dx, int dy)
{
	this->width = width;
	this->height = height;

	if(window->getSize().x != width && window->getSize().y != height)
		window->setSize(sf::Vector2<unsigned int>(width, height));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::View new_view = sf::View(sf::Vector2f( (desktop.width-width)/2, (desktop.height - height/2)/2 ), sf::Vector2f(width, height));
	new_view.setCenter((float) width/2+dx, (float) height/2+dy);
	window->setView( new_view );
}

sf::RenderWindow *  Screen::getWindow()
{
	return window;
}

void Screen::stopDraw()
{
	paused = true;
}

void Screen::resumeDraw()
{
	paused = false;
}
