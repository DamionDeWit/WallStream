


































///// Wall using grid system
/*
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

void Wall::get_dimensions()
{
	//  width
	for (int i = 0; i < Layout[0].size(); i++)
	{
		m_width += Layout[0][i].Width + Layout[0][i].Bezel[1] + Layout[0][i].Bezel[3];
	}
	m_width -= Layout[0][0].Bezel[1] + Layout[0][Layout[0].size()-1].Bezel[3];

	//  height
	for (int i = 0; i < Layout.size(); i++)
	{
		m_height += Layout[i][0].Height + Layout[i][0].Bezel[0] + Layout[i][0].Bezel[2];
	}
	m_height -= Layout[0][0].Bezel[0] + Layout[Layout.size()-1][0].Bezel[2];
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
*/