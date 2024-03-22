
#ifndef __DESTROYABLE_BOX_H__
#define __DESTROYABLE_BOX_H__

#include <memory>
#include <vector>

#include "Hitbox.h"


#include <OEFrame.h>


class DestroyableBox : public Hitbox
{
public:
	DestroyableBox() : Hitbox()
	{

	}
	DestroyableBox(std::string boxName) : Hitbox(boxName)
	{

	}

public:

	

	bool isContains(MathVector vec)
	{
		bool ret = false;

		if (_isBroken == true)
		{
			return ret;
		}
		else
		{
			ret = Hitbox::isContains(vec);
		}

		return ret;

	}

	bool isBroken() { return _isBroken; }

private:

	bool _isBroken = false;

	SDL_Color boxColor = SDLColors::RED;
	SDL_Color boxBorderColor = SDLColors::GREEN;
	int borderThickness = 2;

	std::shared_ptr<OEFrame> texture;

public:

	std::shared_ptr<OEFrame> createBox(IWindowActions* win, MathVector pos, int XLen, int YLen)
	{
		this->setPos(pos);
		this->setXLength(XLen);
		this->setYLength(YLen);
		
		texture = std::make_shared<OEFrame>(win);
		texture->setBounds(pos.X(), pos.Y(), XLen, YLen);

		texture->setBackground(boxColor);

		texture->setBorder(boxBorderColor, borderThickness);
		texture->setBorderActive(true);
		texture->setForeground(boxColor);
		

		texture->setVisible(true);

		_isBroken = false;

		return texture;

	}

	Hitbox::Sides getSide(MathVector vec)
	{
		Sides ret = Sides::NONE;

		_isBroken = true;
		texture->setVisible(false);

		//texture->repaint();

		ret = Hitbox::getSide(vec);

		return ret;

	}

};

class DBoxesBuilder
{
private:
	
	IWindowActions* _win;

	std::vector<std::shared_ptr<Hitbox>>* obstaclesRef;
	

public:

	int XLen = 0;
	int YLen = 0;

	void setXLen(int newLen) { XLen = newLen; }
	void setYLen(int newLen) { YLen = newLen; }

	DBoxesBuilder(IWindowActions* win, std::vector<std::shared_ptr<Hitbox>>* obstacles)
	{
		_win = win;
		obstaclesRef = obstacles;
	}

public:

	std::shared_ptr<OEFrame> createBox(int posX, int posY)
	{
		std::shared_ptr<OEFrame> ret;

		std::shared_ptr<DestroyableBox> tempBox = std::make_shared<DestroyableBox>();

		MathVector pos = MathVector(posX, posY);
		tempBox->setXLength(XLen);
		tempBox->setYLength(YLen);

		ret = tempBox->createBox(_win, pos, XLen, YLen);

		obstaclesRef->push_back(tempBox);

		return ret;

	}




};



#endif // !__DESTROYABLE_BOX_H__


