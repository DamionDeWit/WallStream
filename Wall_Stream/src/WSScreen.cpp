#include <iostream>
#include "WSScreen.h"

Rect::Rect()
{
	Width = 0;
	Height = 0;
	Area = 0;
}

Rect::Rect(int width, int height)
{
	Width = width;
	Height = height;
	Area = Width * Height;
}

void Rect::Print()
{
	std::cout << "Width: " << Width << std::endl;
	std::cout << "Height: " << Height << std::endl;
	std::cout << "Area: " << Area << std::endl;
}