#include <iostream>
#include <string>
#include <vector>
#include <numeric>


#include "config.h"
#include "wall.h"
#include "screen.h"
#include "Video.h"


#define LOG(x) std::cout << x << std::endl
#define LOGRATIO(x) std::cout << x[0] << ":" << x[1] << std::endl
#define PAUSE system("PAUSE")



void run_ffmpeg_screenCap()
{
	const std::string &input = "-f dshow -i video=\"UScreenCapture\"";

	const std::string iplist[] = { "192.168.60.247"
	};

	const std::string &buffer = "ffmpeg -hwaccel cuvid -y -rtbufsize 2000M -f gdigrab -framerate 60 -offset_x 0 -offset_y 0 -video_size 4000x2128 -i desktop -c:v h264_nvenc -preset:v hp -pix_fmt yuv444p -profile:v high444p -f mpegts udp://192.168.60.247:1234";

	system(buffer.c_str());
}
void run_ffmpeg_cuvid()
{
	const std::string &buffer = "ffmpeg -i C:\\Users\\Pi\\Downloads\\720_sample.divx -c:v h264_nvenc -profile:v high444p -pix_fmt yuv444p -preset fast output.mp4 -c:v h264_nvenc -profile:v high444p -pix_fmt yuv444p -preset fast output2.mp4 -c:v h264_nvenc -profile:v high444p -pix_fmt yuv444p -preset fast output3.mp4";

	system(buffer.c_str());
}
void run_ffmpeg_convert()
{
	const std::string &buffer = "ffmpeg -i C:\\Users\\Pi\\Downloads\\4k_sample.mp4 -c:v h264_nvenc -filter:v \"crop=3000:1596:0:0\"  -preset llhq C:\\Users\\Pi\\Downloads\\3k_sample.mp4";

	system(buffer.c_str());
}
void run_ffmpeg_wall()
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

void run_ffmpeg_freeform(Wall wall, Video video)
{

	const std::string inputs[] = { "-i \"C:\\Users\\Pi\\Desktop\\MP4-2c\\Misc Patterns\\C - Convergence\\2-Small 1080p Crosshatch.mp4\" ",
									"-i \"C:\\Users\\Pi\\Desktop\\MP4-2c\\Misc Patterns\\B - Various\\5-Front Projection.mp4\" ",
									"-i \"C:\\Users\\Pi\\Downloads\\720_sample.mp4\" ",
									"-i \"C:\\Users\\Pi\\Downloads\\500x500.mp4\" ",
									"-i \"C:\\Users\\Pi\\Downloads\\3k_sample.mp4\" ",
									"-i \"C:\\Users\\Pi\\Downloads\\4k_sample.mp4\" ",
									};
	const std::string &preset = " -preset ll ";
	const std::string &profile = "-profile:v high444p ";
	const std::string &codec = " -c:v h264_nvenc";
	const std::string &hwaccel = "-hwaccel cuvid -c:v h264_cuvid ";
	const std::string &bufsize = " -bufsize 2000k";
	std::vector<std::string> filters;
	

	//	Generate the crop filter per screen
	for (int i = 0; i < wall.Layout.size(); i++)
	{

		std::string filter = " -filter:v \"";
		//  Start

		//  Pad
		filter.append("pad=");
		filter.append(std::to_string(video.getWidth() + video.getPadding("horizontal")));
		filter.append(":");
		filter.append(std::to_string(video.getHeight() + video.getPadding("vertical")));
		filter.append(":");
		filter.append((std::to_string(video.getPadding("horizontal")/2)));
		filter.append(":");
		filter.append((std::to_string(video.getPadding("vertical")/2)));
		filter.append(":black");

		filter.append(", ");

		//  Crop
		filter.append("crop=");
		filter.append(std::to_string(wall.Layout[i].m_Width));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_Height));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_X));
		filter.append(":");
		filter.append(std::to_string(wall.Layout[i].m_Y));

		
		//  End
		filter.append("\"");
		filters.push_back(filter);
		

	}



	const std::string iplist[] = { "192.168.60.241",
		"192.168.60.242",
		"192.168.60.243",
		"192.168.60.244",
		"192.168.60.245",
		"192.168.60.246",
	};

	std::string buffer = "ffmpeg -re " + inputs[1]
		+ codec + preset + filters[0] + bufsize
		+ " -f mpegts udp://" + iplist[0] + ":1234"
		+ codec + preset + filters[1] + bufsize
		+ " -f mpegts udp://" + iplist[1] + ":1234"
		+ codec + preset + filters[2] + bufsize
		+ " -f mpegts udp://" + iplist[2] + ":1234"
		+ codec + preset + filters[3] + bufsize
		+ " -f mpegts udp://" + iplist[3] + ":1234"
		+ codec + preset + filters[4] + bufsize
		+ " -f mpegts udp://" + iplist[4] + ":1234"
		+ codec + preset + filters[5] + bufsize
		+ " -f mpegts udp://" + iplist[5] + ":1234";

	LOG(buffer);
	system(buffer.c_str());
}

void ffmpeg()
{
	system("ffmpeg -re -i \"C:\\Users\\Pi\\Downloads\\720_sample.divx\" -c:v h264_nvenc -f mpegts udp://192.168.60.241:1234");
}


void main()
{  
	// Variable initialization
	Config c;
	Wall wall(c);
	Video video(1920, 1080);
	std::vector<int> wallContext = wall.getDimensions();

	////  Scale Wall to Video  ////

	//  Scale Wall to match height of video
	wall.scale(double(video.getHeight()) / double(wall.getHeight()));

	if (wall.getWidth() < video.getWidth())
	{
		//  Scale Wall to match width of video
		wall.scale(double( video.getWidth() ) / double( wall.getWidth() ));

		//  Add Vertical Padding
		video.setPadding("vertical", wall.getHeight() - video.getHeight());
	}

	else
	{
		//  Add Horizontal Padding
		video.setPadding("horizontal", wall.getWidth() - video.getWidth());
	}

	LOG("Wall Width:" << wall.getWidth());
	LOG("Wall Height:" << wall.getHeight());
	LOG("Video Width:" << video.getWidth());
	LOG("Video Height:" << video.getHeight());
	LOG("Video Padding Horizontal: " << video.getPadding("horizontal"));
	LOG("Video Padding Vertical: " << video.getPadding("vertical"));




#ifdef OLDSCALING
	//int videoWidth = 1280;
	//int videoHeight = 720;
	//int videoGCD = std::gcd(videoWidth, videoHeight);
	//std::vector< int > videoRatio;
	//videoRatio.push_back(videoWidth/videoGCD);
	//videoRatio.push_back(videoHeight/videoGCD);

	// Match wall and video ratio
	while (double(wall.getRatio()[0])/double(wall.getRatio()[1]) != double(video.getRatio()[0])/double(video.getRatio()[1]))
	{
		if (double(wall.getRatio()[0]) / double(wall.getRatio()[1]) > double(video.getRatio()[0]) / double(video.getRatio()[1]))
			video.m_paddingHorizontal++;

		else
			video.m_paddingVertical++;
		//  Logging some details for debugging
		//LOG(double(videoWidth) / double(wall.m_width));
		
		//LOGRATIO(wall.getRatio());
		//LOG(double(wall.getRatio()[0]) / double(wall.getRatio()[1]));
		//LOGRATIO(video.getRatio());
		//LOG(double(video.getRatio()[0]) / double(video.getRatio()[1]));
		
		//LOG("Width: " << video.m_width + video.m_paddingHorizontal<< " Height: " << video.m_height + video.m_paddingVertical);
	}

	//  Scale wall down to the video
	wall.scaleWidth(double(video.m_height + video.m_paddingVertical) / double(wall.m_height));
	wall.scaleHeight(double(video.m_height + video.m_paddingVertical) / double(wall.m_height));
	//  More logging for debugging 
	//wall.printWall();
	LOG(wallContext[0]);
	LOG(wallContext[1]);
	
	LOG("Video Width:" << video.m_width);
	LOG("Video Padding H:" << video.m_paddingHorizontal);
	LOG("Video Full Width:" << video.m_width + video.m_paddingHorizontal);
#endif

	//  Starting the Wall
	LOG(wallContext[0]);
	LOG(wallContext[1]);
	PAUSE;
	system("python start_omx_on_wall.py");
	run_ffmpeg_freeform(wall, video);
	PAUSE;
}





////  Grid wall
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