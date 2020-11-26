//Implementación de la serpiente
#ifndef SERPIENTE_H
#define SERPIENTE_H

#include "Punto.h"
#include <vector>
#include <ncurses.h>

using namespace std;

class Serpiente {
public:
    Serpiente(const int&, const int&, int = 3, double = 1.0);//v = pix/sec
    //Para mover todo el cuerpo según la nueva posición de la cabeza:
    void moverse(bool, int&);

    //Set y get la velocidad de la serpiente
    void setV(double);
    double getV() const;

    void setD(int);
    int getD() const;
    Punto moverCabeza(int);
    void setCuerpo(vector<Punto> *);
    vector<Punto> *getCuerpo();

private:
    vector<Punto> *cuerpo = new vector<Punto>;
    double V; //Velocidad
    int D; //Dirección hacia donde va, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
    Punto moverCabeza(); //genera una nueva posicion para la cabeza
    
};

#endif
