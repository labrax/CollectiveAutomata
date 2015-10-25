/*
 * Console.hpp
 *
 *  Created on: 25 de out de 2015
 *      Author: Victor R. Cardoso
 */

#ifndef COMMON_CONSOLE_H_
#define COMMON_CONSOLE_H_

#include <cstdio>
#include <cstdarg>

class Console {
private:
	Console();
public:
	static Console & getConsole();
	void log(const char* format, ...);
	~Console();
};

#endif
