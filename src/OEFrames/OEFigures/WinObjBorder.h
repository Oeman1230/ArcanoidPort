
#ifndef __WINDOW_OBJECT_BORDER_H__
#define __WINDOW_OBJECT_BORDER_H__


#include "../OEInterfaces/IWindowActions.h"

#include "WindowDrawPrimitive.h"
#include "WindowLine.h"


class OEWindow;
class WinObjBorder : public WindowDrawPrimitive
{
public:

	WinObjBorder(IWindowActions* mainWin);
	~WinObjBorder();

	struct BorderProperties
	{
		SDL_Rect borderSizes;
		int lineThickness;
		Color borderColor;
	};

public:

	void setBounds(int x, int y, int width, int height);
	void setLocation(int x, int y);
	SDL_Rect getSizes();
	void repaint();
	void setBorder(Color color, int thickness) override;

private:

	void _setColorsToBorders(Color color);
	void _setThicknessToBorders(int thickness);
	void _setBounds();

private:

	BorderProperties _border;

	WindowLine _upBorder;
	WindowLine _rightBorder;
	WindowLine _downBorder;
	WindowLine _leftBorder;


};


#endif // !__WINDOW_OBJECT_BORDER_H__
