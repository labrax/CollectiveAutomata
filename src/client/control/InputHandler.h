/*
 * InputHandler.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SRC_CLIENT_CONTROL_INPUTHANDLER_H_
#define SRC_CLIENT_CONTROL_INPUTHANDLER_H_

#include "../gamestate/PlayerState.h"

class InputHandler {
private:
	PlayerState * ps;
public:
	InputHandler(PlayerState * ps);
	virtual ~InputHandler();
};

#endif /* SRC_CLIENT_CONTROL_INPUTHANDLER_H_ */
