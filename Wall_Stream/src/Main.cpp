#include <iostream>
#include "WSScreen.h"

#define LOG() screen.Print();

int main()
{
	Screen screen(25, 4);
	LOG()

	std::cin.get();
}