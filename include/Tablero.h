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
    
    void setBricks(vector<Punto>*);
    vector<Punto>* getBricks() const;

    int getPuntoIndex(const int, const int, vector<Punto>*);
    void randomXY(int&, vector<Punto> *);

    void printGrid(bool);
    void printMessage(string&);
    void printMessage(string&, int);
    string readLine(string&);
    int printGameOver(bool);
    void printScores( vector<string>*, vector<int>*);

private:
    Serpiente* snake;
    vector<Punto>* presas;
    vector<Punto>* bricks;
    WINDOW* win;

    void printBorder(int);
    string readLine(int, int);
    const vector<vector<int> > gover_pxart = {
        { 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0},
        { 0, 1, 3, 3, 3, 1, 0, 1, 3, 3, 3, 1, 0},
        { 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1},
        { 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1},
        { 1, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 1},
        { 0, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 1, 0},
        { 0, 0, 1, 3, 3, 1, 1, 3, 3, 3, 1, 0, 0},
        { 0, 0, 0, 1, 3, 3, 1, 1, 3, 1, 0, 0, 0},
        { 0, 0, 0, 0, 1, 3, 3, 1, 1, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
    };
};

#endif