
#include "OESDL_Module.h"

#include <iostream>

std::weak_ptr<OESDL_Module> OESDL_ModuleSingleton::_sdlMod_wptr = std::weak_ptr<OESDL_Module>();

//OESDL_Module* OESDL_ModuleSingleton::_sdlModule = NULL;

bool OESDL_ModuleSingleton::wasInit = false;


OESDL_Module::OESDL_Module() 
{
    SDL_init_module();

    _rend = NULL;
    _window = NULL;
    _winSurf = NULL;
      

}


OESDL_Module::OESDL_Module(std::string winName)
{
    throw OESDLModErrors::OldOESDLCode();
    

}


OESDL_Module::~OESDL_Module()
{
    OESDL_ModuleSingleton::clear();

   

    if (_rend != NULL)
    {
        SDL_DestroyRenderer(_rend);
    }
    
    if (_winSurf != NULL)
    {
        SDL_FreeSurface(_winSurf);
    }
    
    

    if (_window != NULL)
    {
        SDL_DestroyWindow(_window);
    }
    
    
    
    _rend = NULL;
    _window = NULL;
    _winSurf = NULL;

    IMG_Quit();
    TTF_Quit();

    std::cout << SDL_GetError() << std::endl;

    SDL_Quit();
    

    

    //_SDL_sys_eManager->send_event("SDL_Main_Module_close", SysESources_e::OESDL_Module_SRC, SysETypes_e::str_message);

	//_SDL_sys_eManager = NULL;

    

}
void OESDL_Module::SDL_init_module()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw OESDLModErrors::CantInitSDLErr();
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        throw OESDLModErrors::CantInitSDLImageErr();
    }

    if (TTF_Init() == -1)
    {
        throw OESDLModErrors::CantInitSDLTTFErr();
    }

}

void OESDL_Module::SDL_init_module(int screenWidth, int screenHeight)
{
    throw OESDLModErrors::OldOESDLCode();

    /*_screen_width = screenWidth;
    _screen_height = screenHeight;

    _window = SDL_CreateWindow(_mainWindowName.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _screen_width, _screen_height, SDL_WINDOW_SHOWN);

    if (_window == NULL)
    {
        throw OESDLModErrors::CantCreateWinErr();
    }

    _winSurf = SDL_GetWindowSurface(_window);

    if (_winSurf == NULL)
    {
        throw OESDLModErrors::CantCreateWinSurfErr();
    }

    _rend = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_rend == NULL)
    {
        throw OESDLModErrors::CantCreateWinRendererErr();
    }

    SDL_Surface* scr = _winSurf;
    SDL_Rect screenRect = { 0,0, _screen_width, _screen_height };
    SDL_FillRect(scr, &screenRect, SDL_MapRGB(scr->format, 200, 200, 200));
    SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(_rend, scr);
    _standartScreen = screenTexture;
    screenTexture = NULL;
    SDL_FreeSurface(scr);*/



}


SDL_Window* OESDL_Module::createMainWinDiscr(std::string winName, int screenWidth, int screenHeight)
{
    
    _screen_width = screenWidth;
    _screen_height = screenHeight;
    _mainWindowName = winName;

    _window = SDL_CreateWindow(winName.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _screen_width, _screen_height, SDL_WINDOW_SHOWN);

    if (_window == NULL)
    {
        throw OESDLModErrors::CantCreateWinErr();
    }

    _winSurf = SDL_GetWindowSurface(_window);

    if (_winSurf == NULL)
    {
        throw OESDLModErrors::CantCreateWinSurfErr();
    }

    _rend = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_rend == NULL)
    {
        throw OESDLModErrors::CantCreateWinRendererErr();
    }

    SDL_Surface* scr = _winSurf;
    SDL_Rect screenRect = { 0,0, _screen_width, _screen_height };
    SDL_FillRect(scr, &screenRect, SDL_MapRGB(scr->format, 200, 200, 200));
    SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(_rend, scr);
    _standartScreen = screenTexture;
    screenTexture = NULL;
    SDL_FreeSurface(scr);

    return _window;

}


SDL_Texture* OESDL_Module::getScreen_Standart_Backhround()
{
    SDL_Texture* ret = _standartScreen;


    int* w = NULL;
    int* h = NULL;

    SDL_GetWindowSize(_window, w, h);

    if (w == NULL || h == NULL)
    {
        return ret;
    }

    if (*w == _screen_width || *h == _screen_height)
    {
        return ret;
    }

    SDL_DestroyTexture(_standartScreen);

    SDL_Surface* scr = _winSurf;

    SDL_Rect screenRect = { 0,0, *w, *h };

    SDL_FillRect(scr, &screenRect, SDL_MapRGB(scr->format, 200, 200, 200));
    SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(_rend, scr);

    SDL_FreeSurface(scr);


    _standartScreen = screenTexture;
    ret = screenTexture;

    screenTexture = NULL;


    return ret;
}

void OESDL_Module::rendPresent()
{
    SDL_RenderPresent(_rend);
}

void OESDL_Module::updateWin()
{
    SDL_UpdateWindowSurface(_window);
}

void OESDL_Module::showWin()
{
    SDL_ShowWindow(_window);
}

void OESDL_Module::rendClear()
{
    SDL_RenderClear(_rend);
}