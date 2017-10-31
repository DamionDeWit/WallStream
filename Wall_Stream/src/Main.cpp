
#include <iostream>
#include <windows.h>
#include <string>
#include "config.h"
#include "screen.h"

#define LOG(x) x.Print();

void run_omxplayer()
{
	system("python C:\\Users\\Pi\\Source\\Repos\\Wall_Stream\\Wall_Stream/start_omx_on_wall.py");
	Sleep(1000);
	
}

void run_ffmpeg()
{
	const std::string &buffer = "ffmpeg -i C:\\Users\\Pi\\Videos\\samples\\sample.divx -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.241:1234 -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*0\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.242:1234 -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*0\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.243:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*1\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.244:1234 -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*1\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.245:1234 -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*1\" -pixel_format yuv444p -preset default -vcodec h264_nvenc -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.246:1234";

	system(buffer.c_str());
}

int main()
{
	run_omxplayer();
	run_ffmpeg();
	system("PAUSE");
}