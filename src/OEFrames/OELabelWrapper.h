#ifndef __OELABEL_WRAPPER_H__
#define __OELABEL_WRAPPER_H__

#include <memory>

#include "BaseWrapper.h"
#include "OEFrameWrapper.h"
#include "OELabel.h"


class OELabelWrapper : public OEFrameWrapper
{
public:

	OELabelWrapper();
	~OELabelWrapper();

	struct LabelProperties
	{
		TTF_Font* _labelFont;
		int _fontSize = 100;

		std::string _labelText;
		std::string _fontPath = std::string("C:/Windows/Fonts/times.ttf");

		SDL_Color _textColor = SDLColors::BLACK;

	} ;

public:

	void setFont(std::string fondDest);
	void setText(std::string newText);
	void setFontSize(int fontSize);
	void setTextColor(Color color);

	void setFrame(std::shared_ptr<OEFrame> newFrame) override;

public:

	std::shared_ptr<BaseWindowObj> build();

protected:

	LabelProperties _labelProperties;
	
	void _applyProperties();

	


};




#endif // !__OELABEL_WRAPPER_H__
