#include <iostream>
#include "WSScreen.h"

#define LOG(x) std::cout << x < std::endl

int main()
{
	Rect r(34, 65);
	r.Print();

	std::cin.get();
}