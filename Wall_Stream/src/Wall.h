#ifndef  WALL_H
#define WALL_H

#include "screen.h"



class Wall
{
public:
	std::vector<Screen> Screens;
	std::vector< std::vector < Screen > > Layout;

	void add_screen(Screen screen);
	void del_screens();

	void add_row();
	void add_to_layout(Screen &screen, int row);	//  Adds screen to layout  - ERROR

};

#endif // ! WALL_H
