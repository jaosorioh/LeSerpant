#ifndef TABLERO_H
#define TABLERO_H

#include "Serpiente.h"
#include <stdlib.h>
#include <string>
#include <time.h>

//color personalizado para ncurses
#define COLOR_GRAY 30
//maximo numero de caracteres que pueden leerse para el nombre del jugador
#define MAX_CHAR 10
//tiempo de espera para actualizar algunos cambios
#define WAIT_TIME 0.6e4

using namespace std;
class Tablero {

public:
    Tablero();
    ~Tablero();

    void setSnake(Serpiente*);
    Serpiente* getSnake() const;

    void setPresas(vector<Punto>*);
    vector<Punto>* getPresas() const;

    int getPuntoIndex(const int, const int, vector<Punto>*);
    void randomXY(int&);

    void printGrid(bool);
    void printMessage(string&);
    string readLine(string&);
    void printGameOver(bool);

private:
    Serpiente* snake;
    vector<Punto>* presas;
    WINDOW* win;

    void printBorder(int);
    string readLine(int, int);
};

#endif