/*
Implementación de la clase Jugador
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../include/Jugador.h"

using namespace std;

Jugador::Jugador( string uName )
{
	//verificar nombre del usuario y archivo

	//set nombre 
	cout << "nombre: " << uName << endl;
}

void Jugador::setPuntaje( int score )
{
	puntaje = score;
}

int Jugador::getPuntaje( void )
{
	return puntaje;
}

void Jugador::setNombre( string name )
{
	nombre = name;
}

string Jugador::getNombre( void )
{
	return nombre;
}