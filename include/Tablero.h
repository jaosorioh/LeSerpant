#ifndef TABLERO_H
#define TABLERO_H

#include "Punto.h"
#include <vector>

using namespace std;
class Tablero {

public:
    Tablero(int *, int *);

    void setN(int *);
    int *getN() const;
    
    void setM(int *);    
    int *getM() const;

    void setPuntos(vector<Punto> *);
    
    vector<Punto> *getPuntos() const;

    Punto *getPunto(int &, int &) const;
    
    void randomXY(int &);
    void update(int &);
    void printGrid();
    char c = '.';

private:
    int *N;
    int *M;
    vector<Punto> *puntos;
    
};

#endif
