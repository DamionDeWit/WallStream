#include <iostream>
#include "wall.h"

Wall::Wall(Config &c)						//  Constuctor for Wall Object
	: m_Config{ c }							//  Sets m_Config to c
{
	//  For each screen in the config, add the screen to the Layout vector
	for (unsigned int i = 0; i < m_Config.m_Screens.size(); i++)
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

	for (unsigned int i = 0; i < Layout.size(); i++)
		x_coords_min.push_back(Layout[i].getLeft());
	
	//  Get lowest x
	int min_x = std::min_element(x_coords_min.begin(), x_coords_min.end())[0];
	
	if (min_x != 0)
	{
		// Add -min_x to every screen's x
		for (unsigned int i = 0; i < Layout.size(); i++)
			Layout[i].transposeX(-min_x);
	}

	//  revaluate min x;
	x_coords_min.clear();

	for (unsigned int i = 0; i < Layout.size(); i++)
		x_coords_min.push_back(Layout[i].getLeft());

	min_x = std::min_element(x_coords_min.begin(), x_coords_min.end())[0];
	//  ^^^ Could be a function ^^^



	//  get Highest X Coord
	std::vector< int > x_coords_max;

	for (unsigned int i = 0; i < Layout.size(); i++)
		x_coords_max.push_back(Layout[i].getRight());
	
	int max_x = std::max_element(x_coords_max.begin(), x_coords_max.end())[0];


	//  VVV Could be a function VVV
	//  check if Lowest Y == 0, if not transpose all screens
	std::vector< int > y_coords_min;

	for (unsigned int i = 0; i < Layout.size(); i++)
		y_coords_min.push_back(Layout[i].getTop());

	//  Get lowest y
	int min_y = std::min_element(y_coords_min.begin(), y_coords_min.end())[0];


	if (min_y != 0)
	{
		// Add -min_y to every screen's y
		for (unsigned int i = 0; i < Layout.size(); i++)
			Layout[i].transposeY(-min_y);
	}

	//  revaluate min y;
	y_coords_min.clear();

	for (unsigned int i = 0; i < Layout.size(); i++)
		y_coords_min.push_back(Layout[i].getLeft());

	min_y = std::min_element(y_coords_min.begin(), y_coords_min.end())[0];
	//  ^^^ Could be a function ^^^

	//  get Highest Y Coord
	std::vector< int > y_coords;

	for (unsigned int i = 0; i < Layout.size(); i++)
		y_coords.push_back(Layout[i].getBottom());

	int max_y = std::max_element(y_coords.begin(), y_coords.end())[0];


	std::vector< int > results;
	results.push_back(max_x);
	results.push_back(max_y);

	m_width = results[0];
	m_height = results[1];

	return results;
}

std::vector< int > Wall::getRatio()			//  Not sure if this is still used, shouldn't be needed for the current way of scaling
{
	std::vector< int > results;
	int gcd = std::gcd(m_width, m_height);
	results.push_back(m_width / gcd);
	results.push_back(m_height / gcd);

	return results;
}

void Wall::scaleWidth(double x)			//  Scale the width of the wall
{
	for (unsigned int i = 0; i < Layout.size(); i++)
	{
		Layout[i].m_Width = int(double(Layout[i].m_Width) * x);			//  Layout[i].m_Width *= x; came with some warnings, this fixed it
		Layout[i].m_X = int(double(Layout[i].m_X) * x);
	}

	m_width = int(double(m_width) * x);
}

void Wall::scaleHeight(double x)		//  Scale the height of the wall
{
	for (unsigned int i = 0; i < Layout.size(); i++)
	{
		Layout[i].m_Height = int(double(Layout[i].m_Height) * x);
		Layout[i].m_Y = int(double(Layout[i].m_Y) * x);
	}

	m_height = int(double(m_height) * x);
}

void Wall::scale(double ratio)			//  Scale the wall, width and height should be equally scaled to not lose the correct aspect ratio
{
	scaleWidth(ratio);
	scaleHeight(ratio);
}

void Wall::scaleLetterbox(Video &video)	
{
	////  Letterbox Scaling ////
	//  Adding a letterbox seems to be heavy on the GPU at high resolutions such as 4K
	//  Worked fine at 720p

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
	//// Fit to Frame Scaling ////
	//  Works great up to 8K (Tested)
	//  Will lose some of the image at top-bottom or left-right if aspect ratio of the video and the wall do not match (overscan effect)

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

void Wall::printWall()				//  For your debugging purposes
{
	for (unsigned int i = 0; i < Layout.size(); i++)
		Layout[i].Print();
}
