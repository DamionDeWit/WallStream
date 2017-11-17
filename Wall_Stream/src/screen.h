#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
	int Width;
	int Height;
	int Bezel[4];		//  0: bezel_top  1: bezel_left  2: bezel_bottom  3: bezel_right

	Screen();																								//  Default: set Width, Height and all Bezels to 0
	Screen(int x);																							//  Set Width and Height to x, all Bezels to 0
	Screen(int width, int height);																			//  Set Width and Height, all Bezels to 0
	Screen(int width, int height, int bezel_all);															//  Set Width and Height, all Bezels to bezel_all
	Screen(int width, int height, int bezel_top_bottom, int bezel_left_right);								//  Set Width and Height, sets Bezels respectively
	Screen(int width, int height, int bezel_top, int bezel_left, int bezel_bottom, int bezel_right);		//  Set Width and Height, sets all Bezels respectively


	void Print() const;
	
};



#endif // !SCREEN_H
