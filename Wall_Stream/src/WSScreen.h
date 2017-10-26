#ifndef WSSCREEN_H
#define WSSCREEN_H

class Rect
{
protected:
	int Width;
	int Height;
	int Area;
public:
	Rect();
	Rect(int width, int height);
	virtual void Print();
};

class Screen : public Rect
{
private:
	const char* Output = "192.168.50.240";
public:
	Screen()
	{
		Width = 0;
		Height = 0;
		Area = 0;
	}

	Screen(int width, int height)
	{
		Width = width;
		Height = height;
		Area = Width * Height;
	}

	void Print() override
	{
		std::cout << "Width: " << Width << std::endl;
		std::cout << "Height: " << Height << std::endl;
		//std::cout << "Area: " << Area << std::endl;
		std::cout << "Output: " << Output << std::endl;
	}
};

#endif // !WSSCREEN_H
