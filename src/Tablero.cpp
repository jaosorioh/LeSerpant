#include <stdlib.h>
#include <time.h>
#include <vector>
#include <curses.h>

#include "../include/Tablero.h"

using namespace std;

Tablero::Tablero(int* N_, int* M_)
{
    setN(N_);
    setM(M_);
    setPuntos(new vector<Punto>);
    int r = 1;
    randomXY(r);
}

void Tablero::setN(int* N_)
{
    N = N_;
}

int* Tablero::getN() const
{
    return N;
}

void Tablero::setM(int* M_)
{
    M = M_;
}

int* Tablero::getM() const
{
    return M;
}

void Tablero::setPuntos(vector<Punto>* puntos_)
{
    puntos = puntos_;
}

vector<Punto>* Tablero::getPuntos() const
{
    return puntos;
}

Punto* Tablero::getPunto(int& f, int& c) const
{
    Punto* p;

    if (getPuntos()->size() == 0)
        p = NULL;
    else {

        int i = 0;
        for (; i < getPuntos()->size(); i++) {
            p = &(getPuntos()->at(i));

            if ((p->getX() == f) && (p->getY() == c)) {
                break;
            }
        }
        if (i == getPuntos()->size()) {

            p = NULL;
        }
    }
    return p;
}

void Tablero::randomXY(int& npuntos)
{
    int i = 0;

    while (i < npuntos) {
        int x = rand() % (*getN()) + 1;
        int y = rand() % (*getM()) + 1;

        if (getPunto(x, y) == NULL) {
            Punto p(x, y, &c);
            getPuntos()->push_back(p);
            i++;
        }
    }
}

void Tablero::update(int& ch)
{

    Punto* p = &(getPuntos()->at(0));
    if(ch == KEY_LEFT)
    {
        p->setX(p->getX() - 1);
        if (p->getX() < 1)
            p->setX(*getN());
    }
    if(ch == KEY_RIGHT)
    {
        p->setX(p->getX() + 1);
        if (p->getX() > (*getN()))
            p->setX(1);
    }
    
    if(ch==KEY_DOWN){
        p->setY(p->getY() + 1);
        if (p->getY() > (*getM()))
            p->setY(1);
    }
    
    if(ch==KEY_UP){
        p->setY(p->getY() - 1);
        if (p->getY() < 1)
            p->setY(*getM());
    }
    
    clrtoeol();
    refresh();
}

void Tablero::printGrid()
{
    clear();
    attron(COLOR_PAIR(1));

    for (int i = 0; i < *getN() + 2; i++) {
        move(0, i);
        addch(' ');
        refresh();
        move(*getM() + 1, i);
        addch(' ');
        refresh();
    }

    for (int j = 0; j < *getM() + 1; j++) {
        move(j, 0);
        addch(' ');
        refresh();
        move(j, *getN() + 1);
        addch(' ');
        refresh();
    }

    attron(COLOR_PAIR(2));

    for (int i = 0; i < getPuntos()->size(); i++) {
        Punto* p = &(getPuntos()->at(i));
        move(p->getY(), p->getX());
        addch(' ');
        refresh();
    }
}
