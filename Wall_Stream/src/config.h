#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include "screen.h"

class Config {
public:		//  To Be Private
	std::vector< Screen > m_Screens;


public:
	Config();

};

#endif // DEBUG_H