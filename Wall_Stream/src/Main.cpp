#include <iostream>

class Rect
{
protected:
	int Width;
	int Height;
	int Area;
public:
	Rect()
	{
		Width = 0;
		Height = 0;
		Area = 0;
	}

	Rect(int width, int height)
	{
		Width = width;
		Height = height;
		Area = Width * Height;
	}

	virtual void Print()
	{
		std::cout << "Width: " << Width << std::endl;
		std::cout << "Height: " << Height << std::endl;
		std::cout << "Area: " << Area << std::endl;
	}
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

int main()
{
	Screen screen{};
	screen.Print();

	std::cin.get();
}