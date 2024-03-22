
#ifndef __OEBUTTON_H__
#define __OEBUTTON_H__

#include <memory>

#include "OEWindow.h"
#include "OELabel.h"
#include "BaseWindowObj.h"
#include "FrameSwapper.h"

class OEButton : public BaseWindowObj
{
public:

	OEButton(OEWindow* mainWin);
	~OEButton();

	bool isClickable() { return _canBeClicked;}
	void setClickable( bool status) { _canBeClicked = status; }
public:
	
	void changeTextureToPressed();
	void changeTextureToUnpressed();
	void setPressedButtonTexture(std::shared_ptr<OEFrame> newTexture);
	void setUnpressedButtonTexture(std::shared_ptr<OEFrame> newTexture);


	void addClickListener(BaseWindowObj::BaseReaction action, void* caller);
	void doClickActions(void* arg);

public:

	virtual void setBounds(int x, int y, int width, int height);
	virtual void setLocation(int x, int y);

	virtual SDL_Rect getSizes() { return _buttonSizes; }

public:

	void repaint();

private:

	OEWindow* _winPtr;

	bool _canBeClicked;

	SDL_Rect _buttonSizes;

	std::vector<BaseWindowObj::BaseListener> _onClickActions;

	//First - unpressed texture
	//Second - pressed texture
	FrameSwapper _buttonTextures;

	/*std::shared_ptr<OEFrame> _currentTexture;

	std::shared_ptr<OEFrame> _pressedButtonTexture;
	std::shared_ptr<OEFrame>  _unpressedButtonTexture;*/



};


#endif // !__OEBUTTON_H__


