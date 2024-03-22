
#ifndef __OEFRAME_H__
#define __OEFRAME_H__

#include <memory>



#include "OEInterfaces/IWindowActions.h"
#include <OETexture.h>

#include "OEFigures/WinObjBorder.h"

//#include "OEWindow.h"
#include "BaseWindowObj.h"

class OEFrame : public BaseWindowObj
{

public:

	OEFrame(IWindowActions* windowI);
	//Do not use. Throws OldRealisation exception
	OEFrame(SDL_Renderer* FrameRenderer);
	virtual ~OEFrame();


	void setBackground(Color color);
	void setForeground(Color color) {};
	//void setVisible(bool newState);

public:

	//void setWindow(OEWindow* newWin) { /*_win = newWin;*/ }
	void setBounds(int x, int y, int width, int height);
	void setLocation(int x, int y);

	void setBorder(Color color, int thickness);
	void setBorderActive(bool status) { _border->setVisible(status); };

	SDL_Rect getSizes();

public:

	void repaintAll();
	void repaint();
	void update() {};

public:

	std::weak_ptr<OETexture> getOETexture() { return frameTexture; }
	//void setText(std::string text);

private:

	
	//void _createBorder();

protected:

	std::shared_ptr<OETexture> frameTexture;
	std::shared_ptr<WinObjBorder> _border;

protected:

	IWindowActions* _win;
	//OEWindow* _win;
	SDL_Renderer* _winRenderer;

};




#endif // !__OEFRAME_H__


