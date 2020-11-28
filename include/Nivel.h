#ifndef NIVEL_H
#define NIVEL_H

#include "Punto.h"
#include <vector>

using namespace std;

class Nivel
{
public:
    Nivel(int, int , bool);
    bool getpasaParedes( void ) const;
    void setpasaParedes(bool);
    int getScore( void ) const;
    void setScore( int);
    int getNPresas( void ) const;
    void setNPresas( int );
    
private:
    int score;
    int npresas;
    bool pasaParedes;
};

#endif