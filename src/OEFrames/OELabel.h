
#ifndef __OELABEL_H__
#define __OELABEL_H__

#include "OEInterfaces/IWindowActions.h"
#include "BaseWindowObj.h"
#include "OEFrame.h"
#include <OESDL_Module.h>

class OELabel : public OEFrame
{
public:

	OELabel(IWindowActions* window);
	OELabel(SDL_Renderer* rend);
	~OELabel();


	void setBackground(Color color);
	void setFontSize(int fontSize);
	void setTextColor(Color color);
	//void setForeground(Color color);
	//void setVisible(bool newState);

public:

	//void setBounds(int x, int y, int width, int height);
	//void setLocation(int x, int y);
	//void setBorder(Color color, int thickness);

	void repaint();

public:
	void setFont(std::string fondDest);
	void setText(std::string newText);

protected:

	TTF_Font* _labelFont = nullptr;
	int _fontSize = 100;

	std::string _labelText;
	std::string _fontPath = std::string("C:/Windows/Fonts/times.ttf");

	
	SDL_Color _textColor;
	SDL_Color _bgColor;

};



#endif // !__OELABEL_H__


