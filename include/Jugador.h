#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

using namespace std;

class Jugador
{
public:
	Jugador( string );
	//~Jugador();

	bool isPlayerinFile(); //comprueba si existe el jugador
	void addMaxScore();

	void setPuntaje( int );
	int getPuntaje( void );

	void setNombre( string );
	string getNombre( void );

private:
	int puntaje;
	string nombre;
	string scoreFile;

};

#endif