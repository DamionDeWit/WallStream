extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "wall.h"
#include "screen.h"
#include "Video.h"


#define LOG(x) std::cout << x << std::endl
#define PAUSE system("PAUSE")				//  system("PAUSE") should be windows only, consider making this multi-platform is needed



void run_ffmpeg_screenCap()					//  *OLD CODE* Old function in which I tried to use a screencapture as input
{
	const std::string &input = "-f dshow -i video=\"UScreenCapture\"";

	const std::string iplist[] = { "192.168.60.247"
	};

	const std::string &buffer = "ffmpeg -hwaccel cuvid -y -rtbufsize 2000M -f gdigrab -framerate 60 -offset_x 0 -offset_y 0 -video_size 4000x2128 -i desktop -c:v h264_nvenc -preset:v hp -pix_fmt yuv444p -profile:v high444p -f mpegts udp://192.168.60.247:1234";

	system(buffer.c_str());
}
void run_ffmpeg_wall()						//  *OLD CODE* Seems to be the starting point of the current function in use
{
	const std::string &input = "-i C:\\Users\\Pi\\Downloads\\4k_sample.mp4 ";
	const std::string &preset = "-preset ultrafast ";
	const std::string &profile = "-profile:v high444p ";
	const std::string &codec = "-c:v h264 ";
	const std::string &hwaccel = "-hwaccel cuvid -c:v h264_cuvid ";
	const std::string &bufsize = "-bufsize 2000k ";
	const std::string filter[] = { 
									(" -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" "), 
									" -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*0\" ",
									" -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*0\" ",
									" -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*1\" ",
									" -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*1\" ",
									" -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*1\" ",
									};

	const std::string iplist[] = {	"192.168.60.241",
									"192.168.60.242",
									"192.168.60.243",
									"192.168.60.244",
									"192.168.60.245",
									"192.168.60.246",
									};

	const std::string &buffer = "ffmpeg -re  "   + input
		+ filter[0] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[0] + ":1234"
		+ filter[1] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[1] + ":1234"
		+ filter[2] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[2] + ":1234"
		+ filter[3] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[3] + ":1234"
		+ filter[4] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[4] + ":1234"
		+ filter[5] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[5] + ":1234";

	system(buffer.c_str());
}

void run_ffmpeg_freeform(Wall wall, Video video, std::string input)				//  Function that's currently in use
{
	//  Be sure to change the dimensions of video in main!!!
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


void main(int argc, char *argv[])
{
	// Variable initialization
	Config c;
	Wall wall(c);
	Video video(7680, 4320);		//  Be sure that this matches the dimensions of the video!!!
	std::string input;

	if (argc >= 2)					//  Is there a video given?
	{
		input = argv[1];			//  Set input to the second argument, first argument is always the location of the program
	}
	else
	{
		LOG("No input file...");
		PAUSE;
		return;
	}

	wall.scaleFitFrame(video);		//  Method of Wall which makes the wall fit in the video

	//  Starting the Wall
	system("python C:\\Users\\Pi\\source\\repos\\Wall_Stream\\Wall_Stream\\start_omx_on_wall.py");
	run_ffmpeg_freeform(wall, video, input);
	PAUSE;
}





////  *OLD CODE* Grid wall
/*void test(Wall &wall)
{
	for (int i = 0; i < 6; i++)
		wall.add_screen(Screen(i, 1280, 1024, 40));


	//for (int i = 0; i < wall.Screens.size(); i++)
	//	wall.Screens[i].Print();
}

void main()
{
	Wall wall;
	
	test(wall);

	wall.add_row();
	wall.add_to_layout(wall.Screens[0], 0);
	wall.add_to_layout(wall.Screens[1], 0);
	wall.add_to_layout(wall.Screens[2], 0);
	wall.add_row();
	wall.add_to_layout(wall.Screens[3], 1);
	wall.add_to_layout(wall.Screens[4], 1);
	wall.add_to_layout(wall.Screens[5], 1);

	wall.print_wall();

	wall.get_dimensions();
	LOG(wall.m_width);
	LOG(wall.m_height);


	system("PAUSE");

 }*/