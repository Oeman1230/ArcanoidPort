
#ifndef __BALL_H__
#define __BALL_H__


#include <memory>
#include "OEUtilities/OEVectorMathTemplate.h"

#include "./OEFrames/OEFrame.h"

typedef Vector2D<int> MathVector;

class Ball
{
public:

	
	Ball() = default;

	Ball(MathVector positionInGameField, MathVector StartVelocity)
	{
		position = positionInGameField;
		velocity = StartVelocity;
	}

	void setBall(Ball newBall)
	{
		this->setPosition(newBall.getPosition());
		this->texture = newBall.texture;
		this->velocity = newBall.velocity;
	}

	/*Ball& operator= (Ball& newBall)
	{
		this->setPosition(newBall.getPosition());
		this->texture = newBall.texture;
		this->velocity = newBall.velocity;

		return *this;
	}*/



private:

	MathVector position;
	MathVector velocity;

	int ballSize;
	std::shared_ptr<OEFrame> texture;

public:

	MathVector getPosition() { return position; }
	void setPosition(MathVector newPos) { position = newPos; }
	MathVector* getPositionPtr() { return &position; }


	MathVector getVelocity() { return velocity; }
	void setVelocity(MathVector newVel) { velocity = newVel; }
	MathVector* getVelocityPtr() { return &velocity; }


	std::shared_ptr<OEFrame> createBall(IWindowActions* win , SDL_Color ballColor, int size)
	{
		texture = std::make_shared<OEFrame>(win);
		
		//!!!!!!!!!!!!!!!!
		
		ballSize = size;

		texture->setBounds((int)position.X(), (int)position.Y(),
			ballSize, ballSize);

		texture->setBackground(ballColor);
		//texture->setForeground(ballColor);

		
		texture->setVisible(true);
		

		//texture->setOpaque(true);

		return texture;
	}

	void update()
	{
		position += velocity;

		//!!!!!!!!!!!!!!!!!!!!!!

		texture->setLocation((int)position.X(), (int)position.Y());

	}

};



#endif // !__BALL_H_



