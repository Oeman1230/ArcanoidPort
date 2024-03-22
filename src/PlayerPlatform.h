
#ifndef __PLAYER_PLATFORM_H__
#define __PLAYER_PLATFORM_H__

#include <memory>

#include "Arc_constants.h"

#include "Arcanoid.h"
#include "OEUtilities/MathVectorExtention.h"

#include "Hitbox.h"
#include "Ball.h"

#include <OEFrame.h>

class PlayerPlatform : public Hitbox
{
private:

	SDL_Color _playerPlatformColor = SDLColors::WHITE;
	SDL_Color _playerPlatformBorderColor = SDLColors::RED;
	int _playerPlatformBorderThickness = 2;

public:

	PlayerPlatform(){}

	PlayerPlatform(Hitbox acceptablePosition) : Hitbox()
	{
		mAcceptablePosition = acceptablePosition;
	}

	MathVector getVelocity() { return velocity; }
	MathVector* getVelocityPtr() { return &velocity; }
	void setVelocity(MathVector vel) { velocity = vel; }

	bool ballColisionDetection(Ball& ball)
	{
		bool ret = false;

		ret = Hitbox::ballColisionDetection(ball);
		
		if (ret == true)
		{
			ball.getPositionPtr()->setY(this->getPos().Y() - ArcContctants::BALL_SIZE);
		}

		return ret;

	}

	std::shared_ptr<OEFrame> createPlatform(IWindowActions* win, int sizeHorizontal, int sizeVertical)
	{
		velocity.setX(0.0);
		velocity.setY(0.0);

		texture = std::make_shared<OEFrame>(win);

		texture->setBounds(this->getPos().X(), this->getPos().Y(),
			sizeHorizontal, sizeVertical);

		texture->setBackground(_playerPlatformColor);
		//texture->setForeground(_playerPlatformColor);
		texture->setVisible(true);
		
		texture->setBorder(_playerPlatformBorderColor, _playerPlatformBorderThickness);
		texture->setBorderActive(true);

		return texture;

	}

	void update()
	{
		MathVector nextPos = MathVector(this->getPos().X() + velocity.X(),
			this->getPos().Y() + velocity.Y());

		if (mAcceptablePosition.isContains(nextPos) == true)
		{
			this->setPos(nextPos);
			texture->setLocation(nextPos.X(), nextPos.Y());

		}

		//texture->repaint();

	}

	PlayerPlatform& operator=(PlayerPlatform newPlatform)
	{
		*this = newPlatform;
		return *this;
	}

private:

	Hitbox mAcceptablePosition;

	std::shared_ptr<OEFrame> texture;
	MathVector velocity;


}

;

#endif // !__PLAYER_PLATFORM_H__


