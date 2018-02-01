/*
//	Video object to represent a video by it's width and height
//	Constructor either gets a string which is the absolute path to the video file
//	or gets integers to manually set the width or height
//	Makes use of the ffmpeg library to obtain width and height
*/

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
	std::vector< int > getRatio();		//  Not in use

	void setPadding(const char* direction, int amount);

private:
	int getPaddingHorizontal() const;
	int getPaddingVertical() const;

	void setPaddingHorizontal(int amount);
	void setPaddingVertical(int amount);


};


#endif