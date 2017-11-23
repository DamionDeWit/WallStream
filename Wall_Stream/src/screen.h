#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

class Screen
{
public:		//  To Be Private
	int m_Width;
	int m_Height;
	int m_Id;
	int m_X;
	int m_Y;

public:

	Screen(int id);																							//  Set Id, defaults rest to 0
	Screen(int id, int x);																					//  Set Width and Height to x
	Screen(int id, int width,int height);																	//  Set Width and Height, all Bezels to 0
	Screen(int id, int width,int height, int x,int y);														//  


	void Print() const;

};




///// Screen using grid system
/*
class Screen
{ 
public:
	int Id;
	int Width;
	int Height;
	int Bezel[4];		//  0: bezel_top  1: bezel_left  2: bezel_bottom  3: bezel_right

	//  Screen();		//  Screen needs an Id																		
	Screen(int id);																									//  Set Id, defaults rest to 0
	Screen(int id, int x);																							//  Set Width and Height to x
	Screen(int id, int width, int height);																			//  Set Width and Height, all Bezels to 0
	Screen(int id, int width, int height, int bezel_all);															//  Set Width and Height, all Bezels to bezel_all
	Screen(int id, int width, int height, int bezel_top_bottom, int bezel_left_right);								//  Set Width and Height, sets Bezels respectively
	Screen(int id, int width, int height, int bezel_top, int bezel_left, int bezel_bottom, int bezel_right);		//  Set Width and Height, sets all Bezels respectively


	void Print() const;
	
};


*/
#endif // !SCREEN_H
