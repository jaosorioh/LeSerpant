#include "../include/Punto.h"

Punto::Punto(int x_, int y_)
{
    setXY(x_, y_);
}

void Punto::setXY(int x_, int y_)
{
    setX(x_);
    setY(y_);
}

void Punto::setX(int x_)
{
    x = x_;
}

void Punto::setY(int y_)
{
    y = y_;
}

int Punto::getX() const
{
    return x;
}

int Punto::getY() const
{
    return y;
}