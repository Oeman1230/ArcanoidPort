
#ifndef __OE_VECTOR_MATH_TEMPLATE_H_
#define __OE_VECTOR_MATH_TEMPLATE_H_

#include <iostream>
#include <math.h>


template <typename T>
class Vector2D
{
public:
	Vector2D() : _x_coord(0), _y_coord(0)//, x(0), y(0)
	{
		
	}
	/*Vector2D(Vector2D<T>& newVec): _x_coord(newVec.x) , _y_coord(newVec.y), x(_x_coord), y(_y_coord)
	{
		
	}*/

	Vector2D(T x, T y): _x_coord(x), _y_coord(y)//, x(_x_coord), y(_y_coord)
	{

	}

	void setVec(Vector2D<T>& newVec)
	{
		_x_coord = newVec.X();
		_y_coord = newVec.Y();
	}

	T X() { return _x_coord; }
	T Y() { return _y_coord; }
	
	void setX(T newX) { _x_coord = newX; }
	void setY(T newY) { _y_coord = newY; }
	
	T getX() { return _x_coord; }
	T getY() { return _y_coord; }

public:
	constexpr Vector2D<T>& operator+=(Vector2D<T>& other)
	{
		_x_coord += other.getX();
		_y_coord += other.getY();
		return *this;
	}

	constexpr Vector2D<T>& operator/=(T div)
	{
		_x_coord /= div;
		_y_coord /= div;
		return *this;
	}

	constexpr Vector2D<T>& operator+(Vector2D<T>& sumVec)
	{
		Vector2D<T> ret(_x_coord + sumVec.X(), _y_coord + sumVec.Y());

		//_x_coord + sumVec.X();
		//_y_coord + sumVec.Y();
		return ret;
	}

public:
	constexpr bool operator==(const Vector2D<T>& compVec)
	{
		bool ret = true;

		if (this->_x_coord != compVec.X())
		{
			ret = false;
		}
		if (this->_y_coord != compVec.Y())
		{
			ret = false;
		}

		return ret;

	}

	constexpr bool operator!=(const Vector2D<T>& compVec)
	{
		bool ret = true;

		if (this->operator==(compVec))
		{
			ret = false;
		}

		return ret;
	}

	Vector2D<T>& operator=(Vector2D<T>&  newVec)
	{
		this->setX(newVec.X());
		this->setY(newVec.Y());
		return *this;
	}

	double len()
	{
		double x_pow2 = std::pow(_x_coord, 2);
		double y_pow2 = std::pow(_y_coord, 2);

		double ret = std::sqrt(x_pow2 + y_pow2);

		return ret;
	}
	//readonly
	//const T& x;
	//readonly
	//const T& y;

	/*void printCoords()
	{
		std::cout << "x= " << this->x << " y= " << this->y << "\n";
	}*/

private:

	T _x_coord;
	T _y_coord;

};

//template <class T>
//constexpr Vector2D<T> operator+=(Vector2D<T> first, Vector2D<T>& second)
//{
//	first += second;
//	return first;
//};

//template <class T>
//constexpr Vector2D<T> operator/(Vector2D<T> first, T second)
//{
//	
//};

template<typename T>
constexpr Vector2D<T> operator/( Vector2D<T> vec, T t) noexcept
{
	vec /= t;
	return vec;
}

template <class T>
constexpr Vector2D<T> operator+( Vector2D<T> first, const Vector2D<T> second)
{
	first += second;
	return first;
	
}



#endif // !__OE_VECTOR_TEMPLATE


