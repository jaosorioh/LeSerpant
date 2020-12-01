/*
Implementación de la clase Nivel
*/
#include "../include/Nivel.h"

using namespace std;

Nivel::Nivel(int s, int np, bool pp, int nb) 
{
    setScore(s); //inicializa el puntaje máximo del nivel
    setNPresas(np); //inicializa el numero de presas del nivel
    setNBricks(nb); //inicializa el número de ladrillos del nivel
    setpasaParedes(pp); //establece si pasa o no las paredes
}

/*
Función para obtener el paso de paredes
OUTPUT: bool
*/
bool Nivel::getpasaParedes( void ) const
{
    return pasaParedes;
}

/*
Función para establecer si pasa paredes
INPUT: bool
*/
void Nivel::setpasaParedes(bool pp)
{
    pasaParedes = pp;
}

/*
Función para obtener el puntaje maximo del nivel
OUTPUT: int
*/
int Nivel::getScore( void ) const
{
    return score;
} 

/*
Función para establecer el puntaje máximo del nivel
INPUT: int
*/
void Nivel::setScore( int s )
{
    score = s;
}

/*
Función para obtener el número de presas 
OUTPUT: int
*/
int Nivel::getNPresas( void ) const
{
    return npresas;
}

/*
Función para establecer el numero de presas
INPUT: int
*/
void Nivel::setNPresas( int np )
{
    if(np < 1)
    {
        np = 1;
    }
    npresas = np;
}

/*
Función para obtener el numero de ladrillos
OUTPUT: int
*/
int Nivel::getNBricks( void ) const
{
    return nbricks;
}

/*
Función para establecer la cantidad de ladrillos
INPUT: int
*/
void Nivel::setNBricks( int nb )
{
    if(nb < 0)
    {
        nb = 0;
    }
    
    nbricks = nb;
}