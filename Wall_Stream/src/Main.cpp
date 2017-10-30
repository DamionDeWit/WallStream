#include <iostream>
#include <string>
#include "config.h"
#include "screen.h"

#define LOG(x) x.Print();

void run_ffmpeg()
{
	const std::string &buffer = "ffmpeg -re -i sample.divx -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.241:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.242:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.243:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.244:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.245:1234 -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k -f mpegts udp://192.168.60.246:1234";

	system(buffer.c_str());
}

int main()
{
	run_ffmpeg();
	system("pwd");
	system("PAUSE");
}