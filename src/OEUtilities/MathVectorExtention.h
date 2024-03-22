
#ifndef __MATH_VECTOR_EXTENSION_H__
#define __MATH_VECTOR_EXTENSION_H__

#include "OEVectorMathTemplate.h"


namespace MathVectors
{
	template <class T>
	void invertX(Vector2D<T>& vec)
	{
		vec.setX(-vec.X());
	}

	template <class T>
	void invertX(Vector2D<T>* vec)
	{
		vec->setX(-vec->X());
	}


	template <class T>
	void invertY(Vector2D<T>& vec)
	{
		vec.setY(-vec.Y());
	}

	template <class T>
	void invertY(Vector2D<T>* vec)
	{
		vec->setY(-vec->Y());
	}

};






#endif // !__MATH_VECTOR_EXTENSION_H_


