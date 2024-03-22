
#ifndef __HITBOX_H__
#define __HITBOX_H__

#include <string>

#include "OEUtilities/OEVectorMathTemplate.h"

#include "Ball.h"

//typedef Vector2D<double> MathVector;

class Hitbox
{
public:
	enum class Sides
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

public:

	std::string boxName;

	Hitbox() { boxName = "NoName"; }
	Hitbox(std::string newName) { boxName = newName; }

private:

	MathVector position;
	double XLength;
	double YLenght;

public:

	MathVector getPos() { return position; }
	void setPos(MathVector newPos) { position = newPos; }

	void setXLength(double len) { XLength = len; }
	void setYLength(double len) { YLenght = len; }

	double getXLength() { return XLength; }
	double getYLength() { return YLenght; }

public:

	virtual bool isContains(MathVector vec);

	double getAngleInCrossingPoint(MathVector vec);

	virtual bool ballColisionDetection(Ball& ball);

	virtual Sides getSide(MathVector vec);

	void update() { return; }

public:

	void setHitbox(Hitbox newBox)
	{
		this->XLength = newBox.XLength;
		this->YLenght = newBox.YLenght;
		this->position = newBox.position;
		this->boxName = newBox.boxName;
	}

	/*Hitbox& operator=(Hitbox& newBox)
	{
		this->XLength = newBox.XLength;
		this->YLenght = newBox.YLenght;
		this->position = newBox.position;
		this->boxName = newBox.boxName;

		return *this;
	}*/

};



#endif // !__HITBOX_H__


