#include <vector>
#include <string>
#include <iostream>
#include "wall.h"



void Wall::add_screen(Screen screen)
{
	Screens.push_back(screen);
}

void Wall::del_screens() 
{
	Screens.clear();
}

void Wall::add_row()
{
	Layout.push_back(std::vector<Screen>());
}


void Wall::add_to_layout(Screen &screen, int row)
{
	Layout[row].push_back(screen);
}

void Wall::print_wall()
{
	std::string line_top_bottom = "+=====+";
	std::string line_left		= "|  ";
	std::string line_right		= "  |";

	for (int i = 0; i < Layout.size(); i++)
	{
		for (int j = 0; j < Layout[i].size(); j++)
		{
			std::cout << line_top_bottom;
		}
		std::cout << std::endl;

		for (int j = 0; j < Layout[i].size(); j++)
		{
			std::cout << line_left << Layout[i][j].Id << line_right;
		}
		std::cout << std::endl;

		for (int j = 0; j < Layout[i].size(); j++)
		{
			std::cout << line_top_bottom;
		}
		std::cout << std::endl;
	}
}
