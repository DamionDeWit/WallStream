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