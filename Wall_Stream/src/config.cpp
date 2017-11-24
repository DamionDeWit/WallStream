#include "config.h"

Config::Config()
{
	//  Default dummy input
	m_Screens.push_back(Screen(0, 1280, 1024, -100, -1000));
	m_Screens.push_back(Screen(1, 1280, 1024, 1280+80, 0));
	m_Screens.push_back(Screen(2, 1280, 1024, (1280+80)*2, 0));
	m_Screens.push_back(Screen(3, 1280, 1024, 0, 1024+80));
	m_Screens.push_back(Screen(4, 1280, 1024, 1280 + 80, 1024 + 80));
	m_Screens.push_back(Screen(5, 1280, 1024, (1280+80)*2, 1024 + 80));
}