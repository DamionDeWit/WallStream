/*
//	Config object which 
//	Loads/Creates Config files
//	Creates Screen objects based on the config file
//	Currently only hold dummy data
*/
#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include "screen.h"

class Config {
public:		//  To Be Private
	std::vector< Screen > m_Screens;


public:
	//	Constructor should try to find a file called config.txt or default.conf or similiar
	//	If found, use this file
	//	Else, let user define new default
	Config();

	//	Method to load config

	//	Method to save current config

	//	Methods to change/adjust current config
	//	Add screen
	//	Delete screen
	//	Edit screem


};

#endif // DEBUG_H