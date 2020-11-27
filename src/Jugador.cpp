/*
Implementación de la clase Jugador
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm> //para hacer el sort 
#include <functional> //para usar greater

#include "../include/Jugador.h"

using namespace std;

Jugador::Jugador()
{
	//set nombre en mayuscula
	string uName = "brayanpapi";

	transform(uName.begin(), uName.end(), uName.begin(), ::toupper);
	
	setName(uName);
	setCurrScore(0);

	//obtener la información de puntajes máximos
	getFileInfo();
}

/*
Función para obtener todos los jugadores en el archivo de puntajes maximos
*/
void Jugador::getFileInfo( void )
{
	string player;
	int maxPoints;
	string isThere = getName();

	allPlayers.clear();
	allScores.clear();

	ifstream puntajes_entr(scoreFile.c_str());

	if (puntajes_entr.fail()) //comprueba la apertura con éxito
	{
		cout << "\nEl archivo no se abrió con éxito"
			 << "\nPor favor compruebe si el archivo existe" << endl;
		exit(1);
	}

	int count = -1;
	int name_index = -1;

	//leemos el contenido
	while (puntajes_entr >> player >> maxPoints)
	{
		count += 1;

		//verificamos si el jugador ya está en la tabla
		if ( player == isThere)
		{
			setMaxScore(maxPoints);
			name_index = count;
		}

		allPlayers.push_back(player);
		allScores.push_back(maxPoints);
	}

	//si el jugador no está en la tabla, establece su puntaje máximo inicial como 0
	if (name_index == -1)
	{
		allPlayers.push_back(isThere);
		allScores.push_back(0);
		name_index = allPlayers.size() - 1;

		setMaxScore(0);
	}

	//ponemos en variable privada
	nameIndex = name_index;

	puntajes_entr.close();

	//cout << "probando indice: " << nameIndex << " " << allPlayers.at(nameIndex) << endl;

}

/*
Función para actualizar el archivo de puntajes máximos
*/
void Jugador::setNewFile( void )
{
	//actualizamos el puntaje maximo
	allScores.at(nameIndex) = maxScore;

	//ordenamos los puntajes de mayor a menor score 
	vector<int> sortScore;

	for (int i=0; i<allScores.size(); i++)
	{
		sortScore.push_back(allScores.at(i));
	}

	sort(sortScore.begin(), sortScore.end(), greater<int>());

	//quitamos los repetidos
	sortScore.erase( unique( sortScore.begin(), sortScore.end()), sortScore.end() );

	//abrimos archivo para escritura
	ofstream puntajes_out(scoreFile.c_str());

	if (puntajes_out.fail()) //comprueba la apertura con éxito
	{
		cout << "\nEl archivo no se abrió con éxito"
			 << "\nPor favor compruebe si el archivo existe" << endl;
		exit(1);
	}

	//escribimos en orden de mayor a menor
	for (int i=0; i<sortScore.size(); i++) 
	{
		for (int j=0; j<allScores.size(); j++)
		{
			if ( sortScore.at(i) == allScores.at(j) )
			{
				puntajes_out << allPlayers.at(j) << " " << allScores.at(j) << endl;
			}
		}
	}

	puntajes_out.close();

}

/*
función que agrega puntos 
INPUT: int
*/
void Jugador::addCurrScore( int tosum)
{
	currScore += tosum;
}

/*
función que actualiza el puntaje máximo al final del juego
*/
void Jugador::checkMaxScore( void )
{
	if (currScore > maxScore)
	{
		maxScore = currScore;
	}
}

/*
Función para establecer el puntaje máximo
INPUT: entero (puntaje maximo)
*/
void Jugador::setMaxScore( int score )
{
	maxScore = score;
}
 
/*
Función para obtener el puntaje máximo
OUTPUT: entero (puntaje maximo)
*/   
int Jugador::getMaxScore( void ) const
{
	return maxScore;
}

/*
Función para establecer el puntaje actual
INPUT: entero (puntaje actual)
*/
void Jugador::setCurrScore( int score )
{
	currScore = score;
}

/*
Función para obtener el puntaje actual
OUTPUT: entero (puntaje actual)
*/
int Jugador::getCurrScore( void ) const
{
	return currScore;
}

/*
Función para establecer el nombre del jugador
INPUT: string (nombre del jugador)
*/
void Jugador::setName( string name)
{
	playerName = name;
}

/*
Función para obtener el nombre del jugador
OUTPUT: string (nombre del jugador)
*/
string Jugador::getName( void ) const
{
	return playerName;
}

