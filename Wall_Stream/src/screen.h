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

	void transposeX(int x);
	void transposeY(int Y);

	int getTop() const;
	int getLeft() const;
	int getBottom() const;
	int getRight() const;

	void Print() const;

};

#endif // !SCREEN_H
