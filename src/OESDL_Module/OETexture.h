
#ifndef __OE_TEXTURE_BASE_H_
#define __OE_TEXTURE_BASE_H_

#include <exception>
#include <memory>

#include "OESDL_Module.h"


typedef std::exception OETextureException;


class OETexture
{
public:
	OETexture(SDL_Renderer* rendererRef);
	OETexture();

	virtual ~OETexture();

	void setRenderer(SDL_Renderer* rend) { _OET_renderer_ref = rend; }

public:



	void free();
	void loadTexture(std::string path);

	SDL_Texture* getSDL_Texture() { return _OET_texture; }
	void setTextureBySurface(SDL_Surface* textureSurf);
	SDL_Surface* getTextureSurfaceCopy();

public:

	void setWidth(int newW) { _OET_width = newW; }
	void setHeight(int newH) { _OET_height = newH; }

	int getWidth() { return _OET_width; }
	int getHeight() { return _OET_height; }

public:

	void setOnScreenPos(int x, int y)
	{
		_OET_onScreenPos.x = x;
		_OET_onScreenPos.y = y;
	}

	SDL_Point getOnScreenPos() { return _OET_onScreenPos; }
	SDL_Rect getOnScreenRect();

public:

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);




protected:

	void setTexture(SDL_Texture* texture, int w, int h);

protected:

	std::string _OET_pathToTexture;

	SDL_Renderer* _OET_renderer_ref;
	
	SDL_Surface* _OET_textureSurface;
	SDL_Texture* _OET_texture;

protected:

	SDL_Point _OET_onScreenPos;
	int _OET_width;
	int _OET_height;



};


#endif // !__OE_SDL_TEXTURE_BASE_H_


