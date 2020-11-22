#include "../include/Punto.h"

Punto::Punto(int x_, int y_, char* c_)
{
    setXY(x_, y_);
    setC(c_); //o para culebra, . para presa
}

void Punto::setC(char* c_)
{
    c = c_;
}

char* Punto::getC() const
{
    return c;
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
