
#include "OEButton.h"

OEButton::OEButton(OEWindow* win)
{
	_canBeClicked = true;
	_winPtr = win;

	_buttonSizes = { 0,0,0,0 };

	win->addMouseClickListener([&](void* caller, void* arg)
		{
			OEButton* button = (OEButton*)caller;

			if (button->isClickable())
			{
				button->changeTextureToPressed();
			}
			
		}, this, ClickManager::Mode::ON_BTN_DOWN);

	win->addMouseClickListener([&](void* caller, void* arg)
		{
			OEButton* button = (OEButton*)caller;

			if (button->isClickable())
			{
				button->changeTextureToUnpressed();				
			}

		}, this, ClickManager::Mode::ON_BTN_UP);

	win->addMouseClickListener([&](void* caller, void* arg)
		{
			OEButton* button = (OEButton*)caller;

			if (button->isClickable())
			{				
				button->doClickActions(arg);
			}

		}, this, ClickManager::Mode::ON_CLICK);



}

OEButton::~OEButton()
{
	_winPtr = nullptr;

}

void OEButton::setBounds(int x, int y, int width, int height)
{
	_buttonSizes = { x, y, width, height };
}

void OEButton::setLocation(int x, int y)
{
	_buttonSizes.x = x;
	_buttonSizes.y = y;
}


void OEButton::changeTextureToPressed()
{
	_buttonTextures.swapToSecond();

}
void OEButton::changeTextureToUnpressed()
{
	_buttonTextures.swapToFirst();

}

void OEButton::setPressedButtonTexture(std::shared_ptr<OEFrame> newTexture)
{
	_buttonTextures.setSecondFrame(newTexture);
}
void OEButton::setUnpressedButtonTexture(std::shared_ptr<OEFrame> newTexture)
{
	_buttonTextures.setFirstFrame(newTexture);
}


void OEButton::addClickListener(BaseWindowObj::BaseReaction action, void* caller)
{
	BaseWindowObj::BaseListener newListener;
	newListener.listener = caller;
	newListener.reaction = action;

	_onClickActions.push_back(newListener);

}

void OEButton::doClickActions(void* arg)
{

	for (auto& it : _onClickActions)
	{
		it.reaction(it.listener, arg);
	}

}

void OEButton::repaint()
{
	auto curFrame = _buttonTextures.getCurrentFrame().lock();
	
	curFrame->repaint();
}
