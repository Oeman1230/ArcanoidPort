
#ifndef __WINDOW_DRAW_PRIMITIVE_H__
#define __WINDOW_DRAW_PRIMITIVE_H__



#include "../BaseWindowObj.h"
#include "../OEInterfaces/IWindowActions.h"


class WindowDrawPrimitive : public BaseWindowObj
{
public:

	WindowDrawPrimitive(IWindowActions* mainWin) : _window(mainWin){}
	virtual ~WindowDrawPrimitive()
	{
		_window = nullptr;
	}

public:

	virtual void setLocation(int x, int y) { throw FunctionNotRealised(); }
	virtual SDL_Rect getSizes() { throw FunctionNotRealised(); }
	virtual void repaint() { throw FunctionNotRealised(); }

public:

	virtual void setBounds(int x, int y, int width, int height) {}
	virtual void setBackground(Color color) {}
	virtual void setForeground(Color color) {}
	virtual void setText(std::string text) {}
	virtual void setBorder(Color color, int thickness) { }
	virtual void add(std::shared_ptr<BaseWindowObj> inpObject) {}
	virtual void update() {}


protected:

	IWindowActions* _window;

};




#endif // !__WINDOW_DRAW_PRIMITIVE_H__


