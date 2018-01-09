#include "screen.h"

//  Constructors
Screen::Screen(int id)
	: m_Id{ id }, m_Width{ 0 },m_Height{ 0 }, m_X{ 0 },m_Y{ 0 }
{

}

Screen::Screen(int id, int x)
	: m_Id{ id }, m_Width{ x }, m_Height{ x }, m_X{ 0 }, m_Y{ 0 }
{

}

Screen::Screen(int id, int width, int height)
	: m_Id{ id }, m_Width{ width }, m_Height{ height }, m_X{ 0 }, m_Y{ 0 }
{

}

Screen::Screen(int id, int width, int height, int x, int y)
	: m_Id{ id }, m_Width{ width },m_Height{ height }, m_X{ x },m_Y{ y }
{

}


void Screen::transposeX(int x)
{
	m_X += x;
}
void Screen::transposeY(int y)
{
	m_Y += y;
}

int Screen::getTop() const{return m_Y;}
int Screen::getLeft() const{return m_X;}
int Screen::getBottom() const{return m_Y + m_Height;}
int Screen::getRight() const{return m_X + m_Width;}



void Screen::Print() const
{
	std::cout << "=======+========" << std::endl;
	std::cout << "      #| " << m_Id << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "  Width| " << m_Width << std::endl;
	std::cout << " Height| " << m_Height << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "      X| " << m_X<< std::endl;
	std::cout << "      Y| " << m_Y<< std::endl;
	std::cout << "=======+========" << std::endl;
}
