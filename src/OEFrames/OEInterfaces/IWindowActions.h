
#ifndef __I_WINDOW_ACTIONS_H__
#define __I_WINDOW_ACTIONS_H__

#include <OESDL_Module.h>

class IWindowActions
{
public:
	//IWindowActions() {};
	virtual ~IWindowActions(){}

	virtual SDL_Renderer* getRend() = 0;
	virtual SDL_Window* getWinDescr() = 0;


};


#endif // !__I_WINDOW_ACTIONS_H__

