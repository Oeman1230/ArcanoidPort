
#ifndef __SDL_COLORS_H__
#define __SDL_COLORS_H__

#include "OESDL_Module.h"


namespace SDLColors
{

	static const SDL_Color BLACK = { 1,1,1, 255 };
	static const SDL_Color WHITE = { 255,255,255, 255 };
	static const SDL_Color GRAY = {64,64,64, 255 };
	static const SDL_Color RED = { 255,0,0, 255 };
	static const SDL_Color GREEN = { 0,255,0, 255 };
	static const SDL_Color BLUE = { 0,0,255, 255 };
	static const SDL_Color PINK = { 255,102,178, 255 };
	static const SDL_Color YELLOW = { 255,255,0, 255 };
	static const SDL_Color ORANGE = { 255,128,0, 255 };
	static const SDL_Color TRANSPARENT = { 0,0,0, 0 };

	static Uint32 toUint(const SDL_PixelFormat *form, const SDL_Color color, Uint8 alp = 255)
	{
		return SDL_MapRGBA(form,color.r, color.g, color.b, alp);
	}

};



#endif // !__SDL_COLORS_H__


