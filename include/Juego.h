
#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include "Jugador.h"

using namespace std;

class Juego 
{

public:
    Juego();
    void jugar();
    
private:
    bool update(int &);
    void mainMenu();
    Jugador *player;
    /*vector<Nivel> niveles;
    int nivel_actual;*/
    Tablero *t;
    const vector<vector<int> > snake_pxart = {
        { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 2, 1, 2, 2, 2, 1, 2, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 0, 0, 0 },
        { 0, 0, 1, 3, 3, 2, 2, 2, 3, 3, 2, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 0, 0, 0 }, 
        { 0, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 0, 0 }, 
        { 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 0 }, 
        { 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1 }, 
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1 }, 
        { 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1 }, 
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0 }

    };
    const vector<string> toprint = {"Le Serpent","Creado por","Nicole Rivera","Brayan Barrera"," John Osorio","Presione ENTER para jugar","ESC para salir"};
};

#endif
