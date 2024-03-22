
#include "./OETexture.h"

#include <iostream>

OETexture::OETexture(SDL_Renderer* rendererRef)
{
	if (rendererRef == NULL)
	{
		throw OETextureException("RENDERER_NULL");
	}

	_OET_renderer_ref = rendererRef;
	_OET_texture = NULL;
	_OET_textureSurface = NULL;
	
	_OET_onScreenPos.x = 0;
	_OET_onScreenPos.y = 0;

	_OET_width = 0;
	_OET_height = 0;
	
	
}

OETexture::OETexture()
{
	

	_OET_renderer_ref = NULL;
	_OET_texture = NULL;
	_OET_textureSurface = NULL;

	_OET_onScreenPos.x = 0;
	_OET_onScreenPos.y = 0;

	_OET_width = 0;
	_OET_height = 0;
}

OETexture::~OETexture()
{
	free();

	_OET_renderer_ref = NULL;

}

void OETexture::free()
{
	if (_OET_texture != NULL)
	{
		SDL_DestroyTexture(_OET_texture);
	}
	_OET_texture = NULL;

	if (_OET_textureSurface != NULL)
	{
		SDL_FreeSurface(_OET_textureSurface);
	}
	_OET_textureSurface = NULL;

	_OET_width = 0;
	_OET_height = 0;

	_OET_onScreenPos.x = 0;
	_OET_onScreenPos.y = 0;

}

void OETexture::loadTexture(std::string pathToTexture)
{
	
	free();

	SDL_Surface* tempSurf = NULL;

	tempSurf = IMG_Load(pathToTexture.c_str());

	if (tempSurf == NULL)
	{
		std::cout << IMG_GetError() << "\n";
		throw OETextureException("CANT_LOAD_SURFACE");
		
	}

	
	setTextureBySurface(tempSurf);


}

void OETexture::setTextureBySurface(SDL_Surface* textureSurface)
{
	

	if (textureSurface == NULL)
	{
		throw OETextureException("NO_SURFACE");
	}

	free();

	_OET_textureSurface = textureSurface;

	SDL_Texture* newTexture = NULL;

	SDL_SetColorKey(textureSurface, SDL_TRUE, SDL_MapRGBA(textureSurface->format, 0, 0, 0,0));

	newTexture = SDL_CreateTextureFromSurface(_OET_renderer_ref, textureSurface);

	if (newTexture == NULL)
	{
		std::cout << SDL_GetError() << "\n";
		throw OETextureException("CANT_CONVERT_TO_TEXTURE");

	}


	setTexture(newTexture, textureSurface->w, textureSurface->h);

}

void OETexture::setTexture(SDL_Texture* texture, int w, int h)
{
	
	_OET_texture = texture;
	_OET_width = w;
	_OET_height = h;
	setBlendMode(SDL_BLENDMODE_BLEND);

}

SDL_Rect OETexture::getOnScreenRect()
{
	SDL_Rect ret;
	ret.x = _OET_onScreenPos.x;
	ret.y = _OET_onScreenPos.y;
	ret.w = _OET_width;
	ret.h = _OET_height;
	return ret;
}


SDL_Surface* OETexture::getTextureSurfaceCopy()
{
	SDL_Surface* ret = NULL;

	if (_OET_texture == NULL)
	{
		throw OETextureException("NO_TEXTURE_TO_COPY");
	}
	
	/*ret = SDL_CreateRGBSurface(0, _OET_textureSurface->w, _OET_textureSurface->h,
		_OET_textureSurface->format->BytesPerPixel, _OET_textureSurface->format->Rmask, _OET_textureSurface->format->Gmask,
		_OET_textureSurface->format->Bmask, _OET_textureSurface->format->Amask);*/

	/*SDL_LockSurface(_OET_textureSurface);
	SDL_LockSurface(ret);*/

	
	ret = SDL_ConvertSurface(_OET_textureSurface, _OET_textureSurface->format ,0);

	//SDL_BlitSurface(textureSurf, NULL, retSurf, NULL);
	/*SDL_UnlockSurface(_OET_textureSurface);
	SDL_UnlockSurface(ret);*/

	if (ret == NULL)
	{
		std::cout << SDL_GetError() << "\n";
		throw OETextureException("SURFACE_CREATION_FAILED");
		
	}


	return ret;
}





void OETexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{

	SDL_SetTextureColorMod(_OET_texture, red, green, blue);

}

void OETexture::setBlendMode(SDL_BlendMode blending)
{

	SDL_SetTextureBlendMode(_OET_texture, blending);

}

void OETexture::setAlpha(Uint8 alpha)
{

	SDL_SetTextureAlphaMod(_OET_texture, alpha);

}


