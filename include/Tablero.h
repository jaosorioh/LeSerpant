#ifndef TABLERO_H
#define TABLERO_H

#include "Serpiente.h"
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;
class Tablero {

public:
    Tablero(int &, int &);

    void setN(int &);
    int getN() const;
    
    void setM(int &);    
    int getM() const;
/*
    void setPuntos(vector<Punto> *);
    
    vector<Punto> *getPuntos() const;
*/
    int getPuntoIndex(const int, const int, vector<Punto> *);
    
    void randomXY(int &);
    bool update(int &);
    
    void printGrid(WINDOW *);
    void printGameOver(WINDOW *);

private:
    int N;
    int M;
    void printBorder(WINDOW *);
    vector<Punto> *presas;
    Serpiente *snake;
    
};

#endif
