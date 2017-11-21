#include <vector>
#include "wall.h"



void Wall::add_screen(Screen screen)
{
	Screens.push_back(screen);
}

void Wall::del_screens() 
{
	Screens.clear();
}

void Wall::add_row()
{
	Layout.push_back(std::vector<Screen>());
}


void Wall::add_to_layout(Screen &screen, int row)
{
	Layout[row].push_back(screen);
}