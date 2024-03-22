
#ifndef __OE_SDL_MODULE_H_
#define __OE_SDL_MODULE_H_

#include <exception>
#include <string>
#include <vector>
#include <memory>

#include "SDL_Include/SDL_INCLUDE.h"

//SDL MODULE NOT SUPPORT SHARED_WEAK_CREATION

typedef std::exception OESDL_ModuleException;

namespace OESDLModErrors
{
	struct BaseError
	{
		std::string errorBody;
		BaseError(std::string errStr) : errorBody(errStr) {};
	};

	struct OldOESDLCode : BaseError { OldOESDLCode() : BaseError("OldOESDLCode") {}; };
	struct NoInstanceErr : BaseError { NoInstanceErr() : BaseError("NoInstanceErr") {}; };
	struct MultipleInstanceErr : BaseError { MultipleInstanceErr() : BaseError("MultipleInstanceErr") {}; };

	struct CantInitSDLErr : BaseError { CantInitSDLErr() : BaseError("CantInitSDLErr") {}; };
	struct CantInitSDLImageErr : BaseError { CantInitSDLImageErr() : BaseError("CantInitSDLImageErr") {}; };
	struct CantInitSDLTTFErr : BaseError { CantInitSDLTTFErr() : BaseError("CantInitSDLTTFErr") {}; };

	struct CantCreateWinErr : BaseError { CantCreateWinErr() : BaseError("CantCreateWinErr") {}; };
	struct CantCreateWinSurfErr : BaseError { CantCreateWinSurfErr() : BaseError("CantCreateWinSurfErr") {}; };
	struct CantCreateWinRendererErr : BaseError { CantCreateWinRendererErr() : BaseError("CantCreateWinRendererErr") {}; };

	

};

typedef std::vector<SDL_Event> SDLModuleEventQueue_T;

class OESDL_Module
{
public:

	
	OESDL_Module();

	OESDL_Module(std::string winName);

	~OESDL_Module();
	
	
	void SDL_init_module(int screenWidth, int screenHeight);
	SDL_Window* createMainWinDiscr(std::string winName, int screenWidth, int screenHeigth);


private:

	void SDL_init_module();

public:

	void rendPresent();
	void updateWin();
	void showWin();
	void rendClear();

public:

	SDL_Renderer* getRend() { return _rend; }
	SDL_Window* getWin() { return _window; }
	SDL_Surface* getWinSurf() { return _winSurf; }

	int get_screen_width() { return _screen_width; }
	int get_screen_height() { return _screen_height; }

private:

	SDL_Texture* _standartScreen;

public:
	SDL_Texture* getScreen_Standart_Backhround();

public:

	SDLModuleEventQueue_T* getEventsQueue() { return &_EventQueue; }
	void setNewEvent(SDL_Event e) { _EventQueue.push_back(e); }
	void clearEventQueue() { _EventQueue.clear(); }
protected:

	SDLModuleEventQueue_T _EventQueue;

	std::string _mainWindowName;

	SDL_Window* _window;
	
	SDL_Surface* _winSurf;

	SDL_Renderer* _rend;
	
	TTF_Font* _sysFont;

	

	int _screen_width;
	int _screen_height;



};


class OESDL_ModuleSingleton
{
private:

	static std::weak_ptr<OESDL_Module> _sdlMod_wptr;

	//static OESDL_Module* _sdlModule;

	static bool wasInit;

public:


	static std::weak_ptr<OESDL_Module> getInstance()
	{
		if (_sdlMod_wptr.expired())
		{
			throw OESDLModErrors::NoInstanceErr();
		}

		return _sdlMod_wptr;

	}

	/*static OESDL_Module* getInstancePtr()
	{
		if (wasInit == false)
		{
			throw OESDLModErrors::NoInstanceErr();
		}


		return _sdlModule;
	}*/

	static void setInstance(std::weak_ptr<OESDL_Module> myself)
	{
		if (_sdlMod_wptr.expired() == false)
		{
			throw OESDLModErrors::MultipleInstanceErr();
		}

		_sdlMod_wptr = myself;
	}

	/*static void setInstance(OESDL_Module* mySelf)
	{
		if (wasInit == true)
		{
			throw OESDLModErrors::MultipleInstanceErr();
		}
		wasInit = true;
		_sdlModule = mySelf;
	}*/

	/*static void clear()
	{
		wasInit = false;
		_sdlModule = NULL;
	}*/

	static void clear()
	{
		_sdlMod_wptr.reset();
	}

};




#endif // !__OE_SDL_MODULE_H_


