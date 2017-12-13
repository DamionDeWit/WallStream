#ifndef VIDEO_H
#define VIDEO_H

#include <vector>
#include <numeric>

class Video
{
private:
	int m_width;
	int m_height;

	int m_paddingHorizontal;
	int m_paddingVertical;

public:
	Video();						//  Set Width and Height to 0
	Video(int x);					//  Set Width and Height to x
	Video(int width, int height);

	int getWidth() const;
	int getHeight() const;

	std::vector< int > getRatio();
};


#endif