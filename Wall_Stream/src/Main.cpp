#include <iostream>
#include <string>
#include "config.h"
#include "screen.h"

#define LOG(x) x.Print();

void run_ffmpeg_screenCap()
{
	const std::string &input = "-f dshow -i video=\"UScreenCapture\"";

	const std::string iplist[] = { "192.168.60.247"
	};

	const std::string &buffer = "ffmpeg -hwaccel cuvid -y -rtbufsize 2000M -f gdigrab -framerate 60 -offset_x 0 -offset_y 0 -video_size 4000x2128 -i desktop -c:v h264_nvenc -preset:v hp -pix_fmt yuv444p -profile:v high444p -f mpegts udp://192.168.60.247:1234";

	system(buffer.c_str());
}

void run_ffmpeg_wall()
{
	const std::string &input = "-i C:\\Users\\Pi\\Videos\\samples\\4k_sample.mp4 ";
	const std::string &preset = "-preset hq ";
	const std::string &profile = "-profile:v high444p ";
	const std::string &codec = "-c:v h264_nvenc ";
	const std::string &hwaccel = "-hwaccel cuvid -c:v h264_cuvid ";
	const std::string &bufsize = "-bufsize 2000k ";
	const std::string filter[] = {
		" -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" ",
		" -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*0\" ",
		" -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*0\" ",
		" -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*1\" ",
		" -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*1\" ",
		" -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*1\" ",
	};

	const std::string iplist[] = { "192.168.60.241",
		"192.168.60.242",
		"192.168.60.243",
		"192.168.60.244",
		"192.168.60.245",
		"192.168.60.246",
	};

	const std::string &buffer = "ffmpeg -re  " + input
		+ filter[0] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[0] + ":1234"
		+ filter[1] + preset + codec + bufsize
		+ " -f mpegts udp://" + iplist[1] + ":1234";

	system(buffer.c_str());
}

int main()
{
	system("python start_omx_on_wall.py");
	run_ffmpeg_wall();
	//system("PAUSE");
}