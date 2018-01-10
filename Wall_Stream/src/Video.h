#ifndef VIDEO_H
#define VIDEO_H

extern "C" {
#include <libavformat/avformat.h>
}

#include <vector>
#include <numeric>
#include <string>

class Video
{
private:
	int m_width;
	int m_height;

	int m_paddingHorizontal;
	int m_paddingVertical;

public:
	Video(std::string &url);			//  Get Width and Height from the url
	Video(int x);					//  Set Width and Height to x
	Video(int width, int height);

	int getWidth() const;
	int getHeight() const;
	int getPadding(const char* direction) const;
	std::vector< int > getRatio();

	void setPadding(const char* direction, int amount);

private:
	int getPaddingHorizontal() const;
	int getPaddingVertical() const;

	void setPaddingHorizontal(int amount);
	void setPaddingVertical(int amount);


};


#endif