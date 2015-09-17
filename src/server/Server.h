/*
 * Server.h
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "gamestate/GameMatrix.h"
#include "../common/network/Network.h"

class Server {
private:
	GameMatrix * gm;
	Network * ns;
public:
	Server();
	virtual ~Server();
	void run();
};

#endif /* SERVER_SERVER_H_ */
