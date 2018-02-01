#include "Video.h"

Video::Video(std::string &url) 
	: m_paddingHorizontal{0}, m_paddingVertical{0}
{
	AVFormatContext *pFormatCtx = NULL;

	// Register all formats and codecs
	av_register_all();

	// Open video file
	if (avformat_open_input(&pFormatCtx, url.c_str(), NULL, NULL) != 0)
	{
		// Couldn't open file
		m_width = NULL;
		m_height = NULL;
	}

	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		m_width = NULL;		// Couldn't find stream information
		m_height = NULL;
	}
	
	// Find the first video stream
	for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_width = pFormatCtx->streams[i]->codecpar->width;
			m_height = pFormatCtx->streams[i]->codecpar->height;
			return;
		}
		else
		{
			m_width = NULL;		// Didn't find a video stream
			m_height = NULL;
		}
	}
}

Video::Video(int x)
	: m_width{x}, m_height{x}, m_paddingHorizontal{ 0 }, m_paddingVertical{ 0 }
{}

Video::Video(int width, int height)
	: m_width{width}, m_height{height}, m_paddingHorizontal{ 0 }, m_paddingVertical{ 0 }
{}

int Video::getWidth() const
{
	return m_width;
}

int Video::getHeight() const
{
	return m_height;
}

int Video::getPaddingHorizontal() const
{
	return m_paddingHorizontal;
}

int Video::getPaddingVertical() const
{
	return m_paddingVertical;
}

int Video::getPadding(const char* direction) const
{
	/// direction: "horizontal" or "vertical"
	if (direction == "horizontal")
		return getPaddingHorizontal();
	else if (direction == "vertical")
		return getPaddingVertical();
	else
		return NULL;
}

std::vector< int > Video::getRatio()
{
	std::vector< int > results;
	int gcd = std::gcd(m_width+m_paddingHorizontal, m_height+m_paddingVertical);
	results.push_back((m_width+m_paddingHorizontal) / gcd);
	results.push_back((m_height+m_paddingVertical) / gcd);

	return results;
}

void Video::setPaddingHorizontal(int amount)
{
	m_paddingHorizontal = amount;
}

void Video::setPaddingVertical(int amount)
{
	m_paddingVertical = amount;
}

void Video::setPadding(const char* direction, int amount)
{
	if (direction == "horizontal")
		setPaddingHorizontal(amount);
	else if (direction == "vertical")
		setPaddingVertical(amount);
		
}