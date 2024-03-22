
#include <SDLColors.h>
#include "WinObjBorder.h"

WinObjBorder::WinObjBorder(IWindowActions* win) : WindowDrawPrimitive(win),
			_upBorder(win), _rightBorder(win), _downBorder(win), _leftBorder(win)
{
	_border.lineThickness = 1;
	_border.borderColor = SDLColors::TRANSPARENT;

	_setColorsToBorders(_border.borderColor);
	_setThicknessToBorders(_border.lineThickness);


	_upBorder.setVisible(true);
	_rightBorder.setVisible(true);
	_downBorder.setVisible(true);
	_leftBorder.setVisible(true);
}

WinObjBorder::~WinObjBorder()
{

}

void  WinObjBorder::_setColorsToBorders(Color color)
{
	_upBorder.setColor(color);
	_rightBorder.setColor(color);
	_downBorder.setColor(color);
	_leftBorder.setColor(color);

}

void  WinObjBorder::_setThicknessToBorders(int thickness)
{
	_upBorder.setThickness(thickness);
	_rightBorder.setThickness(thickness);
	_downBorder.setThickness(thickness);
	_leftBorder.setThickness(thickness);
}


void WinObjBorder::setLocation(int x, int y)
{
	_border.borderSizes.x = x;
	_border.borderSizes.y = y;

	_setBounds();
}

void WinObjBorder::setBounds(int x, int y, int width, int height)
{
	_border.borderSizes = { x, y, width, height };

	_setBounds();
}

void WinObjBorder::_setBounds()
{
	int pixelCorrection = 0;

	if (_border.lineThickness % 2 == 0)
	{
		pixelCorrection = 1;
	}

	int thickness = (_border.lineThickness / 2);


	SDL_Point p1 = { _border.borderSizes.x + thickness, _border.borderSizes.y + thickness };
	SDL_Point p2 = { _border.borderSizes.x + _border.borderSizes.w - thickness, _border.borderSizes.y + thickness };
	SDL_Point p3 = { _border.borderSizes.x + _border.borderSizes.w - thickness,
		_border.borderSizes.y + _border.borderSizes.h - thickness };
	SDL_Point p4 = { _border.borderSizes.x + thickness, _border.borderSizes.y + _border.borderSizes.h - thickness };
	
	/*SDL_Point p1 = { _border.borderSizes.x, _border.borderSizes.y};
	SDL_Point p2 = { _border.borderSizes.x + _border.borderSizes.w, _border.borderSizes.y};
	SDL_Point p3 = { _border.borderSizes.x + _border.borderSizes.w, _border.borderSizes.y + _border.borderSizes.h};
	SDL_Point p4 = { _border.borderSizes.x, _border.borderSizes.y + _border.borderSizes.h};*/

	_upBorder.setBounds(p1.x - thickness, p1.y, p2.x, p2.y);
	_rightBorder.setBounds(p2.x + pixelCorrection, p2.y - thickness, p3.x + pixelCorrection, p3.y + thickness);
	_downBorder.setBounds(p3.x, p3.y + pixelCorrection, p4.x - thickness, p4.y + pixelCorrection);
	_leftBorder.setBounds(p4.x, p4.y, p1.x, p1.y );



}

SDL_Rect WinObjBorder::getSizes()
{
	return _border.borderSizes;
}

void WinObjBorder::repaint()
{
	if (!isVisible)
	{
		return;
	}

	_upBorder.repaint();
	_rightBorder.repaint();
	_downBorder.repaint();
	_leftBorder.repaint();
}

void WinObjBorder::setBorder(Color color, int thickness)
{
	_border.borderColor = color;
	_border.lineThickness = thickness;
	_setColorsToBorders(_border.borderColor);
	_setThicknessToBorders(_border.lineThickness);

	_setBounds();
}

