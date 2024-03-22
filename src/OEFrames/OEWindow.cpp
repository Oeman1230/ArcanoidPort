
#include <thread>
#include <chrono>

#include "OEWindow.h"
#include "OEFrame.h"

#include "../OESDL_Module/OET_Figures/OET_Square.h"

OEWindow::OEWindow()
{

	_SDL_init();

	//isActive = ThreadSafeVar<bool>(false);

	//eReader = std::make_shared<SDL_EventsReader>();
	//SDL_EventReaderSingleton::setInstance(eReader);

	renderHelpTexture = std::make_shared<OETexture>();
	
	renderHelpTexture->setOnScreenPos(0, 0);


	winDescr = NULL;
	renderer = NULL;
	winSurf = NULL;
	bgColor = OEWindow::standartBGColor;

}

OEWindow::~OEWindow()
{

	this->clear();

	this->_SDL_quit();

}

void OEWindow::_SDL_init()
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

void OEWindow::_SDL_quit()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}


void OEWindow::clear()
{
	//isActive.setValue(false);
	//eReader->stopWork();


	//isActive.clear();
	//eReader.reset();

	renderHelpTexture->free();
	renderHelpTexture.reset();

	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (winSurf != NULL)
	{
		SDL_FreeSurface(winSurf);
	}

	if (winDescr != NULL)
	{
		SDL_DestroyWindow(winDescr);
	}

	

	winDescr = NULL;
	renderer = NULL;
	winSurf = NULL;

	SDL_Quit();

}

void OEWindow::_rebuild()
{
	if (winDescr == nullptr)
	{
		return;
	}

	TSquare tempBack = TSquare(renderer);

	int width = renderHelpTexture->getWidth();
	int heigth = renderHelpTexture->getHeight();

	renderHelpTexture->free();

	renderHelpTexture = tempBack.createSquare
	(
		width, heigth, bgColor
	);

}

void OEWindow::makeWindow()
{

	if (renderHelpTexture->getWidth() == 0 || renderHelpTexture->getHeight() == 0)
	{
		throw WrongWindowSize();
	}


	winDescr = SDL_CreateWindow(winName.c_str(),
		renderHelpTexture->getOnScreenPos().x, renderHelpTexture->getOnScreenPos().y,
		renderHelpTexture->getWidth(), renderHelpTexture->getHeight(), SDL_WINDOW_SHOWN);

	

	if (winDescr == NULL)
	{
		throw CantCreateWindow();
	}

	winSurf = SDL_GetWindowSurface(winDescr);

	if (winSurf == NULL)
	{
		throw CantCreateWindowSurface();
	}

	renderer = SDL_CreateRenderer(winDescr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		throw CantCreateWindowRenderer();
	}

	renderHelpTexture->setRenderer(renderer);
	renderHelpTexture->setTextureBySurface(winSurf);

	SDL_RenderCopy(renderer, renderHelpTexture->getSDL_Texture(), 0, 0);

	/*SDL_Surface* scr = winSurf;
	SDL_Rect screenRect = { 0,0, renderHelpTexture->getWidth(), renderHelpTexture->getHeight() };
	SDL_FillRect(scr, &screenRect, SDLColors::toUint(winSurf->format, standartBGColor));

	renderHelpTexture->setTextureBySurface(winSurf);

	scr = NULL;*/

}

void OEWindow::setBounds(int x, int y, int width, int height)
{


	renderHelpTexture->setOnScreenPos(x, y);
	renderHelpTexture->setWidth(width);
	renderHelpTexture->setHeight(height);
	
	if (winDescr != nullptr)
	{
		SDL_SetWindowPosition(winDescr,x, y);
		SDL_SetWindowSize(winDescr,width, height);


	}


}

void OEWindow::setLocation(int x, int y)
{
	renderHelpTexture->setOnScreenPos(x, y);

	if (winDescr != nullptr)
	{
		SDL_SetWindowPosition(winDescr, x, y);
	}

	
}

void OEWindow::setBorder(Color color, int thickness)
{
	throw BaseWindowObj::FunctionNotRealised();
}

void OEWindow::setBackground(Color color)
{
	bgColor = color;

	if (winDescr == nullptr)
	{
		return;
	}

	_rebuild();

}


void OEWindow::repaint()
{
	if (OEWindow::BaseWindowObj::isActive == false)
	{
		return;
	}

	SDL_RenderClear(renderer);
	//SDL_UpdateWindowSurface(winDescr);


	SDL_Texture* screenTexture = nullptr;
	screenTexture = renderHelpTexture->getSDL_Texture();
	SDL_RenderCopy(renderer, screenTexture, 0, 0);
	
	for (auto& it : _innerWinObjects)
	{
		std::shared_ptr<OEFrame> itFrame = std::dynamic_pointer_cast<OEFrame>(it);

		if (itFrame == nullptr)
		{
			try
			{
				it->repaint();
			}
			catch (const FunctionNotRealised&)
			{

			}
			continue;
		}

		itFrame->repaintAll();

	}


	SDL_RenderPresent(renderer);
	
	

}


void OEWindow::startMainThread()
{
	//

	_rebuild();
	SDL_ShowWindow(winDescr);

	isActive =true;
	//eReader->setActive(true);

	try
	{
		while (isActive)
		{

			//eReader->pollEvents();

			SDL_Event e;

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					isActive = false;
					break;
				}
				
				_clickManager.handleClick(&e);

				notifyEventsListeners((void*)(&e));

			}

			


			repaint();


		}
	}
	catch (OESDLModErrors::NoInstanceErr&)
	{

	}
	catch (BaseWindowObj::BaseWinObjErr& baseErr)
	{
		std::cout << "Window main: " << baseErr.body << "\n";
	}
	catch (...)
	{
		
	}

	
}

