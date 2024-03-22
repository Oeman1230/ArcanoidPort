
#ifndef __OEWINDOW_H__
#define __OEWINDOW_H__

#include <thread>
#include <memory>
#include <vector>

#include <OESDL_Module.h>
#include <SDLColors.h>
#include <OETexture.h>

//#include "./SDLMonitor/ThreadsafeVar.h"
//#include "./SDL_EventsReader/SDL_EventsReader.h"
#include "./ClickManager/ClickManager.h"

#include "OEInterfaces/IWindowActions.h"

#include "BaseWindowObj.h"


class OEWindow : public BaseWindowObj, public IWindowActions
{
public:

	struct WrongWindowSize : BaseWinObjErr { WrongWindowSize() : BaseWinObjErr("WrongWindowSize") {} };
	struct CantCreateWindow : BaseWinObjErr { CantCreateWindow() : BaseWinObjErr("CantCreateWindow") {}};
	struct CantCreateWindowSurface : BaseWinObjErr { CantCreateWindowSurface() : BaseWinObjErr("CantCreateWindowSurface") {} };
	struct CantCreateWindowRenderer : BaseWinObjErr { CantCreateWindowRenderer() : BaseWinObjErr("CantCreateWindowRenderer") {} };

	const SDL_Color standartBGColor = SDLColors::WHITE;
	const SDL_Color standargFGColor = SDLColors::BLACK;
	const int updatesPerSecond = 60;

public:

	
	OEWindow();
	~OEWindow();

public:

	void makeWindow();
	void setWinName(std::string newName) { winName = newName; }
	std::string getWinName() { return winName; }


private:

	void _SDL_init();
	void _SDL_quit();
	void _rebuild();

public:

	void clear();
	void startMainThread();

public:

	virtual void setBounds(int x, int y, int width, int height);
	virtual void setLocation(int x, int y);
	virtual void setBorder(Color color, int thickness);

public:

	virtual void setBackground(Color color);
	virtual void setForeground(Color color) { throw FunctionNotRealised(); }

public:

	virtual void repaint();
	SDL_Renderer* getRend() { return renderer; }
	ClickManager* getClickManager() { return &_clickManager; }
	SDL_Window* getWinDescr() { return winDescr; };

	void addMouseClickListener(std::function<void(void*, void*)> action, void* listener, ClickManager::Mode mode = ClickManager::Mode::ON_CLICK)
	{
		_clickManager.addMouseListener(action, listener, mode);
	}

protected:

	//std::shared_ptr<OESDL_Module> sdlModuleRef;
	SDL_Window* winDescr;
	SDL_Surface* winSurf;
	SDL_Renderer* renderer;
	std::shared_ptr<OETexture> renderHelpTexture;
	SDL_Color bgColor;

	std::string winName;
	
	ClickManager _clickManager;

protected:


	//ThreadSafeVar<bool> isActive;
	//std::shared_ptr<SDL_EventsReader> eReader;


};



#endif // !__OEWINDOW_H__


