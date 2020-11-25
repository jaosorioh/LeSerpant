/*
Implementación de la clase Nivel
*/

#include <vector>

#include "../include/Nivel.h"

using namespace std;

Nivel::Nivel( int uN, int uM) 
{
	//fijar tamaño de tablero
	n = uN;
	m = uM;

}

bool Nivel::getpasaParedes( void ) const
{
	return pasaParedes;
}

int Nivel::getN( void ) const
{
	return n;
} 

int Nivel::getM( void ) const
{
	return m;
}
