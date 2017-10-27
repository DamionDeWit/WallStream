#ifndef WSSCREEN_H
#define WSSCREEN_H

class Screen
{
protected:
	int Width;
	int Height;
	int Area;
public:
	Screen();
	Screen(int width, int height);
	void Print() const;
};



#endif // !WSSCREEN_H
