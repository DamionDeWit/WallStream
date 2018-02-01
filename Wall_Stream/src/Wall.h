/*
//	Wall object to represent a video wall by it's width and height
//	Creates a wall based on a config object which contains a layout
//	Has 2 methods for scaling:
//		Using a letterbox (Adding blackbars)
//		Cropping wall to fit the frame (Possible overscan)
*/
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
	std::vector< Screen > Layout;		//  Vector which stores all the screen objects

	//  offsets are needed to center the wall to the frame when using scaleFitFrame
	int offset_x;
	int offset_y;
private:		
	int m_width;
	int m_height;

	Config m_Config;

	void scaleWidth(double x);
	void scaleHeight(double x);
public:

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

#endif // ! WALL_H
