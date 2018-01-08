#ifndef  WALL_H
#define WALL_H

#include <algorithm>
#include <numeric>
#include "screen.h"
#include "config.h"
#include "Video.h"

class Wall
{
public:
	int offset_x;
	int offset_y;
private:		
	int m_width;
	int m_height;

	Config m_Config;

	void scaleWidth(double x);
	void scaleHeight(double x);
public:
	std::vector< Screen > Layout;

	Wall(Config &c);					//  Wall needs a config 
	
	int getWidth() const;
	int getHeight() const;

	std::vector< int > getDimensions();
	std::vector< int > getRatio();
	
	void scale(double ratio);
	void scaleLetterbox(Video &video);
	void scaleFitFrame(Video &video);

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
