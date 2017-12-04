#ifndef  WALL_H
#define WALL_H

#include <algorithm>
#include "screen.h"
#include "config.h"

class Wall
{
public:		// public for testing purposes, private for non-testing
	int m_width;
	int m_height;

	Config m_Config;

public:
	std::vector< Screen > Layout;

	Wall(Config &c);					//  Wall needs a config 
	
	std::vector< int > getDimensions();
	void scaleWidth(double ratio);
	void scaleHeight(double ratio);

	void printWall();

};



///// Wall using grid system
/*
class Wall
{
public:		// public for testing purposes, private for non-testing
	int m_width;
	int m_height;

public:
	std::vector<Screen> Screens;
	std::vector< std::vector < Screen > > Layout;

	void add_screen(Screen screen);
	void del_screens();

	void add_row();
	void add_to_layout(Screen &screen, int row);	//  Adds screen to layout

	void get_dimensions();

	void print_wall();

};
*/

#endif // ! WALL_H
