
#include "Arcanoid.h"

#include "Hitbox.h"
#include <exception>

#include "OEUtilities/MathVectorExtention.h"


#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>





bool Hitbox::isContains(MathVector vec)
{

    bool ret = false;

    if (!(this->getPos().X() <= vec.X()
        && vec.X() <= (this->getPos().X() + this->getXLength())))
    {
        return ret;
    }
    if ((this->getPos().Y() <= vec.Y()
        && vec.Y() <= (this->getPos().Y() + this->getYLength())))
    {
        ret = true;
    }

    return ret;
}

double Hitbox::getAngleInCrossingPoint(MathVector vec)
{
    double ret = 0.0;


    double cosAngle = 0.0;
    double sinAngle = 0.0;

    double angle = 0.0;

    //Определение угла
    try
    {
        //Временные дополнительные переменные для обработки
        double Px_plus_XlenDiv2 = (this->getPos().X() +
            (this->getXLength() / 2));
        double Py_plus_YlenDiv2 = (this->getPos().Y() +
            (this->getYLength() / 2));

        //создание вектора приходящей точки, относительно центра поля
        MathVector VColliding = MathVector(
            vec.X() - Px_plus_XlenDiv2
            ,
            vec.Y() - Py_plus_YlenDiv2
        );
        //Центральный вектор
        MathVector VCenterLine = 
            MathVector( this->getXLength() / 2, 0 );

        //определение косинусной составляющей угла поворота
        double nomin = (VCenterLine.X() * VColliding.X());
        double denomin = (VCenterLine.len() * VColliding.len());

        cosAngle = std::acos(nomin / denomin);

        //Центральный вектор, направленный из цента поля вверх
        MathVector VYCenter = MathVector(0, this->getYLength() / 2);

        nomin = (VYCenter.Y() * VColliding.Y());
        denomin = (VYCenter.len() * VColliding.len());
        //Нахождение синусной составляющей угла
        sinAngle = std::asin(nomin / denomin);

    }
    catch (std::exception ex)
    {
        std::cout << "divide to zero\n";
        return ret;
    }

    //Проверка в какой полуплоскости находится проверяемая точка
    if (sinAngle > 0)
    {
        angle = cosAngle;
    }
    else
    {
        angle = (M_PI * 2) - cosAngle;

    }

    ret = angle;
    return ret;
}

bool Hitbox::ballColisionDetection(Ball& ball)
{
    MathVector tempVec = MathVector(position);

    MathVector centerPos = MathVector(ball.getPosition().X() + (Arcanoid::BALL_SIZE / 2),
        ball.getPosition().Y() + (Arcanoid::BALL_SIZE/2));

    for (int i = 0; i < 4; i++)
    {


        tempVec.setX(centerPos.X() +
        (Arcanoid::BALL_SIZE/2)*(std::cos(M_PI / 2 * i)));

        tempVec.setY(centerPos.Y() +
            (Arcanoid::BALL_SIZE / 2) * (std::sin(M_PI / 2 * i)));

        if (this->isContains(tempVec))
        {

            Hitbox::Sides side = this->getSide(centerPos);

            switch (side)
            {
            case Hitbox::Sides::UP:
                MathVectors::invertY(ball.getVelocityPtr());
                break;
            case Hitbox::Sides::DOWN:
                MathVectors::invertY(ball.getVelocityPtr());
                break;
            case Hitbox::Sides::LEFT:
                MathVectors::invertX(ball.getVelocityPtr());
                break;
            case Hitbox::Sides::RIGHT:
                MathVectors::invertX(ball.getVelocityPtr());
                break;
            case Hitbox::Sides::NONE:
                break;
            default:
                break;
            }

            return true;
        }
    }

    return false;
}

Hitbox::Sides Hitbox::getSide(MathVector vec)
{
    Sides ret = Sides::NONE;

    double angle = this->getAngleInCrossingPoint(vec);

    double fi_1 = std::atan(this->getYLength() / this->getXLength());

    if ((0 <= angle && angle < fi_1) || (M_PI * 2 - fi_1 < angle && angle <= M_PI * 2))
    {
        ret = Sides::RIGHT;
    }
    if (fi_1 < angle && angle < M_PI - fi_1)
    {
        ret = Sides::UP;
    }

    if (M_PI - fi_1 < angle && angle < M_PI + fi_1)
    {
        ret = Sides::LEFT;
    }
    if (M_PI + fi_1 < angle && angle < M_PI * 2 - fi_1)
    {
        ret = Sides::DOWN;
    }
    return ret;


}

