#include <iostream>
#include <fstream>
#include "config.h"

void Config::createDefaultConfig()
{
	std::ofstream config("config.txt");
	config << "# Config File" << std::endl;
	for (int i = 0; i < 6; i++)
	{
		config << std::endl;
		config << "################" << std::endl;
		config << "ID=" << i << std::endl;
		config << "WIDTH=" << "iw/3" << std::endl;
		config << "HEIGHT=" << "ih/3" << std::endl;
		config << "X=" << "iw/3*" << i%3 << std::endl;
		config << "Y=" << "ih/3*" << i/3 << std::endl;


	}
}

Config::Config()
{
	std::cout << "Config Object Created" << std::endl;
	Config::createDefaultConfig();
}

Config::Config(const char* fileName)
{
	std::cout << "Config Object Created" << std::endl;

}

Config::~Config()
{
	std::cout << "Config Destroyed" << std::endl;
}
