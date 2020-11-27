
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string> 
#include <vector>

using namespace std;

class Jugador {
public:
    Jugador(string);
    //~Jugador();

    void setNewFile( void );

    void setMaxScore( int );
    int getMaxScore( void ) const;

    void setCurrScore( int );
    int getCurrScore( void ) const;

    void setName( string );
    string getName( void ) const;

private:

    void getFileInfo( void );

    int currScore;
    int maxScore;
    int nameIndex;
    string playerName;
    const string scoreFile = "HighScore.txt";

    //vectores para almacenar la información de puntaje máximo
    vector<string> allPlayers;
    vector<int> allScores;
};

#endif