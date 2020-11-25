//Implementación de la serpiente

#ifndef SERPIENTE_H
#define SERPIENTE_H
#include "Tablero.h"
#include "Punto.h"
#include <string>
#include <vector>
#include <curses.h>

using namespace std;

class Serpiente {
public:
	Serpiente( int, double );
	Serpiente();

	//Para actualizar la posición de todo el cuerpo según la posición de la cabeza:
	void Posicion(bool);

	//Set y get la longitud de la serpiente
	void setL( int );
	int getL() const;

	//Set y get la velocidad de la serpiente
	void setV( double );
	double getV() const;
	
    
private:
	vector<Punto> cuerpo;	//Inicialmente tiene 4 puntos
	int L;		//Longitud
	double V;	//Velocidad
	int direccion;	//Dirección hacia donde va: 0,1,2,3 = arriba, abajo, izquierda, derecha

	void flechas();
	
	Punto moverse();


};

#endif
