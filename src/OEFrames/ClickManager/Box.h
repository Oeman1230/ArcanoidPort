
#ifndef _BOX_H_
#define _BOX_H_

#include "OEVectorMathTemplate.h"

template<typename T>
class Box
{
public:
    T left;
    T top;
    T width; // Must be positive
    T height; // Must be positive

    constexpr Box(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept :
        left(Left), top(Top), width(Width), height(Height)
    {

    }

    constexpr Box(Vector2D<T>& position, Vector2D<T>& size) noexcept :
        left(position.X()), top(position.Y()), width(size.X()), height(size.Y())
    {

    }

    constexpr T getRight() const noexcept
    {
        return left + width;
    }

    constexpr T getBottom() const noexcept
    {
        return top + height;
    }

    constexpr Vector2D<T> getTopLeft() const noexcept
    {
        return Vector2D<T>(left, top);
    }

    constexpr Vector2D<T> getCenter() const noexcept
    {
        return Vector2D<T>(left + width / 2, top + height / 2);
    }

    constexpr Vector2D<T> getSize() const noexcept
    {
        return Vector2D<T>(width, height);
    }

    constexpr bool contains(Box<T>& box) const noexcept
    {
        return left <= box.left && box.getRight() <= getRight() &&
            top <= box.top && box.getBottom() <= getBottom();
    }

    constexpr bool intersects(Box<T>& box) const noexcept
    {
        return !(left >= box.getRight() || getRight() <= box.left ||
            top >= box.getBottom() || getBottom() <= box.top);
    }
};



#endif // !_BOX_H_


