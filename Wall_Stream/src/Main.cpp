#include <iostream>
#include <string>
#include <vector>
#include "config.h"
#include "wall.h"
#include "screen.h"

#define LOG(x) std::cout << x << std::endl




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

void mainw()
{
	system("python start_omx_on_wall.py");
	run_ffmpeg_wall();

	system("PAUSE");
}


int main()
{
	Screen s(0, 123, 456);
	s.Print();

	system("PAUSE");
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