#include <iostream>
#include "wall.h"

Wall::Wall(Config &c)
	: m_Config{ c }
{
	for (int i = 0; i < m_Config.m_Screens.size(); i++)
		Layout.push_back(m_Config.m_Screens[i]);

	getDimensions();
}

int Wall::getWidth() const
{
	return m_width;
}

int Wall::getHeight() const
{
	return m_height;
}


std::vector< int > Wall::getDimensions()
{

	//  VVV Could be a function VVV
	//  check if Lowest X == 0, if not transpose all screens
	std::vector< int > x_coords_min;

	for (int i = 0; i < Layout.size(); i++)
		x_coords_min.push_back(Layout[i].getLeft());
	
	//  Get lowest x
	int min_x = std::min_element(x_coords_min.begin(), x_coords_min.end())[0];
	
	if (min_x != 0)
	{
		// Add -min_x to every screen's x
		for (int i = 0; i < Layout.size(); i++)
			Layout[i].transposeX(-min_x);
	}

	//  revaluate min x;
	x_coords_min.clear();

	for (int i = 0; i < Layout.size(); i++)
		x_coords_min.push_back(Layout[i].getLeft());

	min_x = std::min_element(x_coords_min.begin(), x_coords_min.end())[0];
	//  ^^^ Could be a function ^^^



	//  get Highest X Coord
	std::vector< int > x_coords_max;

	for (int i = 0; i < Layout.size(); i++)
		x_coords_max.push_back(Layout[i].getRight());
	
	int max_x = std::max_element(x_coords_max.begin(), x_coords_max.end())[0];


	//  VVV Could be a function VVV
	//  check if Lowest Y == 0, if not transpose all screens
	std::vector< int > y_coords_min;

	for (int i = 0; i < Layout.size(); i++)
		y_coords_min.push_back(Layout[i].getTop());

	//  Get lowest y
	int min_y = std::min_element(y_coords_min.begin(), y_coords_min.end())[0];


	if (min_y != 0)
	{
		// Add -min_y to every screen's y
		for (int i = 0; i < Layout.size(); i++)
			Layout[i].transposeY(-min_y);
	}

	//  revaluate min y;
	y_coords_min.clear();

	for (int i = 0; i < Layout.size(); i++)
		y_coords_min.push_back(Layout[i].getLeft());

	min_y = std::min_element(y_coords_min.begin(), y_coords_min.end())[0];
	//  ^^^ Could be a function ^^^

	//  get Highest Y Coord
	std::vector< int > y_coords;

	for (int i = 0; i < Layout.size(); i++)
		y_coords.push_back(Layout[i].getBottom());

	int max_y = std::max_element(y_coords.begin(), y_coords.end())[0];


	std::vector< int > results;
	results.push_back(max_x);
	results.push_back(max_y);

	m_width = results[0];
	m_height = results[1];

	return results;
}

std::vector< int > Wall::getRatio()
{
	std::vector< int > results;
	int gcd = std::gcd(m_width, m_height);
	results.push_back(m_width / gcd);
	results.push_back(m_height / gcd);

	return results;
}

void Wall::scaleWidth(double ratio)
{
	for (int i = 0; i < Layout.size(); i++)
	{
		Layout[i].m_Width *= ratio;
		Layout[i].m_X *= ratio;
	}

	m_width *= ratio;
}

void Wall::scaleHeight(double ratio)
{
	for (int i = 0; i < Layout.size(); i++)
	{
		Layout[i].m_Height *= ratio;
		Layout[i].m_Y *= ratio;
	}

	m_height *= ratio;
}

void Wall::scale(double ratio)
{
	scaleWidth(ratio);
	scaleHeight(ratio);
}

void Wall::scaleLetterbox(Video &video)
{
	////  Letterbox Scaling ////
	//  Scale Wall to match height of video
	scale(double(video.getHeight()) / double(getHeight()));

	if (getWidth() < video.getWidth())
	{
		//  Scale Wall to match width of video
		scale(double(video.getWidth()) / double(getWidth()));

		//  Add Vertical Padding
		video.setPadding("vertical", getHeight() - video.getHeight());
	}
	else
	{
		//  Add Horizontal Padding
		video.setPadding("horizontal", getWidth() - video.getWidth());
	}
}

void Wall::scaleFitFrame(Video &video)
{
	//  Scale to fit frame
	scale(double(video.getWidth()) / double(getWidth()));

	if (getHeight() > video.getHeight())
	{
		//  set wall height equal to video height
		scale(double(video.getHeight()) / double(getHeight()));

		//  add x offset
		offset_x = (video.getWidth() - getWidth()) / 2;
	}
	else
	{
		//  add y offset
		offset_y = (video.getHeight() - getHeight()) / 2;
	}
}

void Wall::printWall()
{
	for (int i = 0; i < Layout.size(); i++)
		Layout[i].Print();
}








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