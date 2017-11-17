#ifndef  WALL_H
#define WALL_H

#include "screen.h"


class Wall
{
public:
	std::vector<Screen> screens;

	void add_screen(Screen screen);
	void del_screen(int index);
};

#endif // ! WALL_H
