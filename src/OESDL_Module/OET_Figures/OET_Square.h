
#ifndef __OE_TEXTURE_SQUARE_H_
#define __OE_TEXTURE_SQUARE_H_

#include "../OESDL_Module.h"
#include "../OETexture.h"

#include <memory>

class TSquare
{
public:

	

	//TSquare(SDL_Renderer* rend, SDL_Surface* windSurf)
	//{
	//	_rend_ref = rend;
	//	_windowSurface_ref = windSurf;
	//}

	TSquare(SDL_Renderer* rend)
	{
		_rend_ref = rend;
	}

	~TSquare()
	{
		_rend_ref = NULL;
	}


	std::shared_ptr<OETexture> createSquare(int width, int heigth, SDL_Color color)
	{

		std::shared_ptr<OETexture> ret = std::make_shared<OETexture>(_rend_ref);
		
		if (width <= 0 || heigth <= 0)
		{
			std::cout << SDL_GetError();
			throw OESDLModErrors::BaseError("WrongSizes");
		}

		SDL_Surface* mySurf = SDL_CreateRGBSurface(0, width, heigth,
			32, 0, 0, 0, 0);

		SDL_SetSurfaceBlendMode(mySurf, SDL_BLENDMODE_BLEND);

		

		if (mySurf == nullptr)
		{
			std::cout << SDL_GetError();
			throw OESDLModErrors::BaseError("CantBlitSurface");
		}

		int status = SDL_FillRect(mySurf, NULL, SDL_MapRGBA(mySurf->format, color.r, color.g, color.b, color.a));

		

		if (status != 0)
		{
			std::cout << SDL_GetError();
			throw OESDLModErrors::BaseError("CantFillSurfaceByColor");
		}

		

		ret->setTextureBySurface(mySurf);




		return ret;
	}

	//std::shared_ptr<OETexture> createSquare(int width, int height, SDL_Color color)
	//{
	//	//OETexture* ret = NULL;
	//	

	//	std::shared_ptr<OETexture> square = std::make_shared<OETexture>(_rend_ref);
	//	SDL_Rect inputRect = { 0,0, width, height };

	//	SDL_Surface* constructTempSurface = SDL_CreateRGBSurfaceWithFormat(_windowSurface_ref->flags, width, height, 32,
	//		_windowSurface_ref->format->format);

	//	if (constructTempSurface == NULL)
	//	{
	//		throw OETextureException("cantConstructSurface");
	//		
	//	}

	//	SDL_FillRect(constructTempSurface, &inputRect, SDL_MapRGBA(constructTempSurface->format,
	//		color.r, color.g, color.b, color.a));

	//	//SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(_rend_ref, constructTempSurface);

	//	square->setTextureBySurface(constructTempSurface);

	//	constructTempSurface = NULL;

	//	return square;
	//}

	/*OETexture* createSquare2(int width, int height, SDL_Color color)
	{
		//OETexture* ret = NULL;


		OETexture* square = new OETexture(_rend_ref);


		SDL_Rect inputRect = { 0,0, width, height };



		SDL_Surface* constructTempSurface = SDL_CreateRGBSurfaceWithFormat(_windowSurface_ref->flags, width, height, 32,
			_windowSurface_ref->format->format);



		if (constructTempSurface == NULL)
		{
			throw OETextureException("cantConstructSurface");

		}


		SDL_FillRect(constructTempSurface, &inputRect, SDL_MapRGBA(constructTempSurface->format,
			color.r, color.g, color.b, color.a));

		//SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(_rend_ref, constructTempSurface);

		square->setTextureBySurface(constructTempSurface);

		constructTempSurface = NULL;

		return square;
	}*/

private:

	//SDL_Window* _winRef;
	SDL_Renderer* _rend_ref;
	//SDL_Surface* _windowSurface_ref;


};




#endif // !__OE_TEXTURE_SQUARE_H_


