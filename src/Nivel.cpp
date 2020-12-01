/*
Implementación de la clase Nivel
*/
#include "../include/Nivel.h"

using namespace std;

Nivel::Nivel(int s, int np, bool pp, int nb) 
{
    setScore(s);
    setNPresas(np);
    setNBricks(nb);
    setpasaParedes(pp);
    
}

bool Nivel::getpasaParedes( void ) const
{
    return pasaParedes;
}

void Nivel::setpasaParedes(bool pp)
{
    pasaParedes = pp;
}

int Nivel::getScore( void ) const
{
    return score;
} 

void Nivel::setScore( int s )
{
    score = s;
}

int Nivel::getNPresas( void ) const
{
    return npresas;
}

void Nivel::setNPresas( int np )
{
    if(np < 1)
    {
        np = 1;
    }
    npresas = np;
}

int Nivel::getNBricks( void ) const
{
    return nbricks;
}

void Nivel::setNBricks( int nb )
{
    if(nb < 0)
    {
        nb = 0;
    }
    
    nbricks = nb;
}

