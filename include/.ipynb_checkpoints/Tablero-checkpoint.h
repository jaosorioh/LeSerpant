#ifndef TABLERO_H
#define TABLERO_H

#include "Serpiente.h"
#include <stdlib.h>
#include <string>
#include <time.h>


#define N 20
#define M 40

using namespace std;
class Tablero {

public:
    Tablero();
    ~Tablero();
    Serpiente * getSnake() const;

    void setSnake(Serpiente *);

    vector<Punto> *getPresas() const;

    void setPresas(vector<Punto> *);
    int getPuntoIndex(const int, const int, vector<Punto> *);
    void randomXY(int &);
    
    void printGrid();
    void printGameOver();

private:
    void printBorder();
    vector<Punto> *presas;
    Serpiente *snake;
    WINDOW *win;
};

#endif
