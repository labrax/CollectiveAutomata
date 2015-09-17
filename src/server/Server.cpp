/*
 * Server.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: Victor R. Cardoso
 */

#include "Server.h"

Server::Server() {
	gm = new GameMatrix();
	ns = new Network();
}

Server::~Server() {
	delete(gm);
	delete(ns);
}

void Server::run() {
	bool isRunning = true;
	while(isRunning) {
		//network
		//gamematrix
		break;
	}
}
