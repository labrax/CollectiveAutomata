/*
 * InputHandler.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_CONTROL_INPUTHANDLER_H_
#define SRC_CLIENT_CONTROL_INPUTHANDLER_H_

#include <SFML/Window/Event.hpp>

#include "PlayerState.hpp"
#include "Screen.hpp"
#include "Console.hpp"

#define MIN_SIZE 5
#define MAX_SIZE 50

class InputHandler {
private:
	
public:
	InputHandler();
	virtual ~InputHandler();
	void poolEvents(Screen * screen);
};

#endif
