#include <iostream>
#include <string>
#include "config.h"
#include "screen.h"

#define LOG(x) x.Print();

void run_ffmpeg()
{
	const std::string &input = "4k_sample.mp4";
	const std::string &preset = "ultrafast";
	const std::string &vcodec = "libx264";

	const std::string iplist[] = {	"192.168.60.241", 
									"192.168.60.242", 
									"192.168.60.243", 
									"192.168.60.244",
									"192.168.60.245",
									"192.168.60.246" };

	const std::string &buffer = "ffmpeg -re -i " + input
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[0] + ":1234"
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*0\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[1] + ":1234"
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*0\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[2] + ":1234"
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*1\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[3] + ":1234"
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*1\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[4] + ":1234"
		+ " -filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*1\" -preset " + preset + " -vcodec " + vcodec + " -tune zerolatency -bufsize 30000k -f mpegts udp://" + iplist[5] + ":1234";

	system(buffer.c_str());
}

int main()
{
	run_ffmpeg();
	system("pwd");
	system("PAUSE");
}