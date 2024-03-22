
#include "WindowLine.h"

#include <SDL2_gfxPrimitives.h>

#define _USE_MATH_DEFINES
#include <math.h>

WindowLine::WindowLine(IWindowActions* win) : WindowDrawPrimitive(win)
{
	_line.thickness = 1;
}

WindowLine::~WindowLine()
{

	

}

void WindowLine::setLocation(int x, int y)
{
	int deltX = (_line.end.x - _line.start.x);
	int deltY = (_line.end.y - _line.start.y);

	_line.start.x = x;
	_line.start.y = y;
	_line.end.x = x + deltX;
	_line.end.y = y + deltY;

	
	/*int minX = std::min(_line.start.x, _line.end.x);
	int minY = std::min(_line.start.y, _line.end.y);

	int maxX = std::max(_line.start.x, _line.end.x);
	int maxY = std::max(_line.start.y, _line.end.y);
	 
	

	_line.start = { minX + (deltX / 2), minY + (deltY / 2) };
	_line.end = { minX + (deltX / 2), minY + (deltY / 2) };*/

}

SDL_Rect WindowLine::getSizes()
{
	int minX = std::min(_line.start.x, _line.end.x);
	int minY = std::min(_line.start.y, _line.end.y);

	int maxX = std::max(_line.start.x, _line.end.x);
	int maxY = std::max(_line.start.y, _line.end.y);

	int width = std::abs(maxX - minX);
	int heigth = std::abs(maxY - minY);

	return { minX, minY, width, heigth };

}

void WindowLine::repaint()
{

	if (this->isVisible == false)
	{
		return;
	}

	SDL_Color color = _line.color;

	SDL_SetRenderDrawColor(_window->getRend(), color.r, color.g, color.b, color.a);

	SDL_FPoint p1 = { _line.start.x, _line.start.y };
	SDL_FPoint p2 = { _line.end.x, _line.end.y};
	
	//double phi = std::atan((p2.y - p1.y) / (p2.x - p1.x));
	
	//std::vector<SDL_FPoint> 
	
	GFX_thickLineRGBA(_window->getRend(), p1.x, p1.y, p2.x, p2.y, _line.thickness, color.r, color.g, color.b, color.a);

	//SDL_RenderSetScale(_window->getRend(), _line.thickness, _line.thickness);
	//SDL_RenderDrawLineF(_window->getRend(), p1.x, p1.y, p2.x, p2.y);
	
	/*for (int i = 0; i < _line.thickness; ++i)
	{
		for (int radIt = 0; radIt < 2; ++radIt)
		{
			SDL_FPoint tempP1 = { p1.x + i * (std::cos(M_PI * radIt + phi)),
								 p1.y + i * (std::sin(M_PI * radIt - phi)) };

			SDL_FPoint tempP2 = { p2.x + i * (std::cos(M_PI * radIt + phi)),
								 p2.y + i * (std::sin(M_PI * radIt - phi)) };

			SDL_RenderDrawLineF(_window->getRend(), tempP1.x, tempP1.y, tempP2.x, tempP2.y);
		}
	}*/
		
		
		/*
		 
        tempVec.setX(centerPos.x +
        (Arcanoid::BALL_SIZE/2)*(std::cos(M_PI / 2 * i)));

        tempVec.setY(centerPos.y +
            (Arcanoid::BALL_SIZE / 2) * (std::sin(M_PI / 2 * i)));
		*/
	

	//SDL_RenderClear(_window->getRend());
	


}

void WindowLine::setBounds(int x1, int y1, int x2, int y2)
{
	SDL_Point p1 = { x1, y1 };
	SDL_Point p2 = { x2, y2 };

	_line.start = p1;
	_line.end = p2;


}
