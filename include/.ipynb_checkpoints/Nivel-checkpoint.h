#ifndef NIVEL_H
#define NIVEL_H

#include "Punto.h"
#include <vector>

using namespace std;

class Nivel
{
public:
	Nivel( int, int );

	int nPresas( void );

	vector<Punto> presas();

	bool getpasaParedes( void ) const;
	int getN( void ) const;
	int getM( void ) const;

private:
	int m;
	int n;
	bool pasaParedes;

};

#endif