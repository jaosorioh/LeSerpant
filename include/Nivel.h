#ifndef NIVEL_H
#define NIVEL_H

#include "Punto.h"
#include <vector>

using namespace std;

class Nivel
{
public:
    Nivel(int, int , bool, int);
    bool getpasaParedes( void ) const;
    void setpasaParedes(bool);
    int getScore( void ) const;
    void setScore( int);
    int getNPresas( void ) const;
    void setNPresas( int );
    int getNBricks (void ) const;
    void setNBricks( int );
    
private:
    int score;
    int npresas;
    bool pasaParedes;
    int nbricks;//num de ladrillos, 0 si ninguno
};

#endif