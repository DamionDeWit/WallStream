#include "Video.h"

Video::Video() 
	: m_width{0}, m_height{0}, m_paddingHorizontal{0}, m_paddingVertical{0}
{}

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

std::vector< int > Video::getRatio()
{
	std::vector< int > results;
	int gcd = std::gcd(m_width+m_paddingHorizontal, m_height+m_paddingVertical);
	results.push_back((m_width+m_paddingHorizontal) / gcd);
	results.push_back((m_height+m_paddingVertical) / gcd);

	return results;
}