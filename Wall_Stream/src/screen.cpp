#include <iostream>
#include "screen.h"

/*Screen::Screen()
	: Width{ 0 }, Height{ 0 }, Bezel{ 0,0,0,0 }
{}*/

Screen::Screen(int id)
	: Id{ id }, Width{ 0 }, Height{ 0 }, Bezel{ 0,0,0,0 }
{}

Screen::Screen(int id, int x)
	: Id{ id }, Width{ x }, Height{ x }, Bezel{ 0,0,0,0 }
{}

Screen::Screen(int id, int width, int height)
	: Id {id}, Width{ width }, Height{ height }, Bezel{ 0,0,0,0 }
{}

Screen::Screen(int id, int width, int height, int bezel_all)
	: Id{ id }, Width{ width }, Height{ height }, Bezel{ bezel_all, bezel_all, bezel_all, bezel_all }
{}

Screen::Screen(int id, int width, int height, int bezel_top_bottom, int bezel_left_right)
	: Id{ id }, Width{ width }, Height{ height }, Bezel{ bezel_top_bottom, bezel_left_right, bezel_top_bottom, bezel_left_right }
{}			   
			   
Screen::Screen(int id, int width, int height, int bezel_top, int bezel_left, int bezel_bottom, int bezel_right)
	: Id{ id }, Width{ width }, Height{ height }, Bezel{ bezel_top, bezel_left, bezel_bottom, bezel_right }
{}

void Screen::Print() const
{
	std::cout << "Id: " << Id << std::endl;
	std::cout << "Width: " << Width << std::endl;
	std::cout << "Height: " << Height << std::endl;
	std::cout << "Bezels: " 
		<< Bezel[0] << ", "
		<< Bezel[1] << ", "
		<< Bezel[2] << ", "
		<< Bezel[3] << std::endl << std::endl;

}

