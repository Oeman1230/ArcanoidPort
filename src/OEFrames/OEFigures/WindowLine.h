
#ifndef __OEF_LINE_H__
#define __OEF_LINE_H__

#include "../OEInterfaces/IWindowActions.h"
#include "WindowDrawPrimitive.h"


class WindowLine : public WindowDrawPrimitive
{
public:

	WindowLine(IWindowActions* win);
	~WindowLine();
 
	struct LineProperties
	{
		SDL_Point start;
		SDL_Point end;
		int	thickness;
		SDL_Color color;
	};

public:

	//move LineProperties::start and ::end to other location from start (x,y)
	virtual void setLocation(int x, int y);
	virtual void setBounds(int x1, int y1, int x2, int y2) override;
	virtual SDL_Rect getSizes();

	virtual void repaint();

public:

	virtual void setColor(SDL_Color newColor) { _line.color = newColor; }
	virtual void setThickness(int newThickness) { _line.thickness = newThickness; }

private:

	LineProperties _line;

};



#endif // !__OEF_LINE_H__

