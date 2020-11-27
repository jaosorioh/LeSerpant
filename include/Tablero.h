#ifndef TABLERO_H
#define TABLERO_H

#include "Serpiente.h"
#include <stdlib.h>
#include <string>
#include <time.h>

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
    string readLine(string &);
    string readLine(int, int);
    void printMessage(string &);

private:
    void printBorder();
    vector<Punto> *presas;
    Serpiente *snake;
    WINDOW *win;
};

#endif
