#include "OELabel.h"
#include "BaseWindowObj.h"
#include <OESDL_Module.h>
#include <SDLColors.h>

OELabel::OELabel(IWindowActions* window) : OEFrame(window)
{
	setFont(_fontPath);

	//_textBackground = std::make_shared<OETexture>(rend);

	_textColor = SDLColors::BLACK;
	_bgColor = SDLColors::BLACK;
	_bgColor.a = 0;
}

OELabel::OELabel(SDL_Renderer* rend) : OEFrame(rend)
{
	auto err = BaseWindowObj::OldRealisation();
	err.body.append("\tOLD_OELABEL_REALISATION");
	throw err;
	


}



OELabel::~OELabel()
{

	if (_labelFont != nullptr && TTF_WasInit())
	{
		TTF_CloseFont(_labelFont);
	}
	_labelFont = nullptr;

	//_textBackground->free();
	//_textBackground.reset();

}


void OELabel::setFontSize(int fontSize)
{

	TTF_CloseFont(_labelFont);

	_fontSize = fontSize;

	TTF_OpenFont(_fontPath.c_str(), fontSize);

}

void OELabel::setBackground(SDL_Color newColor)
{
	_bgColor = newColor;
	
}

void OELabel::setTextColor(SDL_Color color)
{
	_textColor = color;
	
}

void OELabel::setFont(std::string fontDest)
{
	if (_labelFont != nullptr)
	{
		TTF_CloseFont(_labelFont);
	}

	//HygothicExtra.ttf
	//C:/Windows/Fonts/*.ttf
	
	_labelFont = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	std::cout << TTF_GetError();
	if (_labelFont == nullptr)
	{
		throw BaseWinObjErr("No_FONT");
	}
		


}

void OELabel::setText(std::string newText)
{
	_labelText = newText;

	if (newText.size() <= 0)
	{
		return;
	}

	SDL_Rect curRect = frameTexture->getOnScreenRect();

	//frameTexture->free();

	//SDL_Surface* tempSurf = TTF_RenderText_Blended(_labelFont, _labelText.c_str(), _textColor);// , bgColor);

	//if (tempSurf == nullptr)
	//{
	//	throw BaseWinObjErr("CANT_CREATE_TEXT");
	//}
	
	SDL_Surface* tempSurf;
	

	//frameTexture->setTextureBySurface(tempSurf);
	
	

	tempSurf = TTF_RenderText_LCD(_labelFont, _labelText.c_str(), _textColor,_bgColor);

	if (tempSurf == nullptr)
	{
		throw BaseWinObjErr("CANT_CREATE_TEXT");
	}

	frameTexture->setTextureBySurface(tempSurf);

	frameTexture->setWidth(curRect.w);
	frameTexture->setHeight(curRect.h);
	frameTexture->setOnScreenPos(curRect.x, curRect.y);

	

	//frameTexture->setWidth(curPos.w);
	//frameTexture->setHeight(curPos.h);

}


void OELabel::repaint()
{
	//OEFrame::repaint();


	SDL_Texture* thisBack = frameTexture->getSDL_Texture();

	if (thisBack == nullptr)
	{
		throw BaseWinObjErr("NO_TEXTURE");
	}

	if (isVisible == false)
	{
		return;
	}

	SDL_Rect onScreenTextureRect = frameTexture->getOnScreenRect();

	SDL_RenderCopy(_winRenderer, thisBack, 0, &onScreenTextureRect);

	_border->repaint();

}

