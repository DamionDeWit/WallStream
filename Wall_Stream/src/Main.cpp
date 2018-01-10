extern "C" {
#include <libavformat/avformat.h>
}

#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "wall.h"
#include "screen.h"
#include "Video.h"


#define LOG(x) std::cout << x << std::endl
#define PAUSE system("PAUSE")				//  system("PAUSE") should be windows only, consider making this multi-platform if needed


void run_ffmpeg_freeform(Wall wall, Video video, std::string input)
{
	const std::string &preset = " -preset fast ";
	const std::string &profile = "-profile:v high444p ";
	const std::string &codec = " -c:v h264_nvenc";
	const std::string &hwaccel = "-hwaccel cuvid -c:v h264_cuvid ";
	const std::string &bufsize = " -bufsize 2000k";
	std::vector<std::string> filters;


	//	Generate the filters per screen
	for (unsigned int i = 0; i < wall.Layout.size(); i++)
	{
		std::string filter = " -filter:v \"";
		//  Start

		//  Pad
		if (video.getPadding("horizontal") || video.getPadding("vertical"))		//  Check if there is padding applied
		{
			filter.append("pad=");
			filter.append(std::to_string(video.getWidth() + video.getPadding("horizontal")));
			filter.append(":");
			filter.append(std::to_string(video.getHeight() + video.getPadding("vertical")));
			filter.append(":");
			filter.append((std::to_string(video.getPadding("horizontal") / 2)));
			filter.append(":");
			filter.append((std::to_string(video.getPadding("vertical") / 2)));
			filter.append(":black");

			filter.append(", ");
		}
		//  Crop
		filter.append("crop=");
		filter.append(std::to_string(wall.Layout[i].m_Width));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_Height));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_X + wall.offset_x));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_Y + wall.offset_y));

		//  End

		filter.append("\"");
		filters.push_back(filter);
	}



	std::vector<std::string> iplist = {				//  IP of each Pi, should become dynamic based on a config
		"192.168.60.241",
		"192.168.60.242",
		"192.168.60.243",
		"192.168.60.244",
		"192.168.60.245",
		"192.168.60.246"
	};


	//  Generate a command which starts ffmpeg with the required arguments

	std::string buffer = "ffmpeg -re -i \"" + input + "\" ";		//  Start by executing ffmpeg and giving the input

	for (unsigned int i = 0; i < iplist.size(); i++)				//  Generate an output for each screen
	{
		buffer	+=	codec + preset + filters[i] + bufsize
				+	" -f mpegts udp://" + iplist[i] + ":1234";
	}

	LOG(buffer);													//  Log your command before executing, comes in handy for debugging
	system(buffer.c_str());											//  Start ffmpeg
}


void main(int argc, char* argv[])
{
	// Variable initialization
	Config c;
	Wall wall(c);
	std::string input;

	if (argc >= 2)					//  Is there a video given?
		input = argv[1];			//  Set input to the second argument, first argument is always the location of the program
	else
	{
		LOG("No input file...");
		PAUSE;
		return;
	}

	Video video(input);		//  Be sure that this matches the dimensions of the video!!!
	wall.scaleFitFrame(video);		//  Method of Wall which makes the wall fit in the video

	//  Starting the Wall
	system("python C:\\Users\\Pi\\source\\repos\\Wall_Stream\\Wall_Stream\\start_omx_on_wall.py");
	run_ffmpeg_freeform(wall, video, input);
	PAUSE;
}