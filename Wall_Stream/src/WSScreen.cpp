#include <iostream>
#include "WSScreen.h"

Screen::Screen()
	: Width{ 0 }, Height{ 0 }, Area{ 0 }
{}

Screen::Screen(int width, int height)
	: Width{ width }, Height{ height }, Area{ Width * Height }
{}

void Screen::Print() const
{
	std::cout << "Width: " << Width << std::endl;
	std::cout << "Height: " << Height << std::endl;
	std::cout << "Area: " << Area << std::endl;
}
