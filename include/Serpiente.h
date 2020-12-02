//Implementación de la serpiente
#ifndef SERPIENTE_H
#define SERPIENTE_H

#include "Punto.h"		//Incluimos punto para el cuerpo y la cabeza
#include <vector>		//El cuerpo es un vector de puntos
#include <ncurses.h>	//Necesitamos esto para casi todo xd

#define N 22
#define M 44
#define xmin 2
#define ymin 1			
#define aum 1.0			//Para aumentar la velocidad
#define Vmin 5.0		//Velocidad minima (Antes de esta es demasiado lento)
#define Vmax 30.0		//Velocidad máxima (Después de esta demasiado rápido)

using namespace std;

class Serpiente {
public:
    Serpiente(int = 3, double = Vmin);	//constructor, recibe longitud inicial y velocidad (v= pix/sec)
    ~Serpiente();						//Destructor
    void moverse(int&);				    //Para mover todo el cuerpo según la nueva posición de la cabeza
    void comer(Punto &);				//Hacer crecer la serpiente y aumentar la velocidad cuándo come
    void setV(double);					//Set y get la velocidad de la serpiente
    double getV() const;
    void setD(int);						//Set y get la dirección hacia donde va
    int getD() const;
    void modVel();						//Aumentar la velocidad
    Punto moverCabeza(int, bool&);		//método para mover cabeza
    void setCuerpo(vector<Punto> *);	//Set y get cuerpo
    vector<Punto> *getCuerpo();			

private:
    vector<Punto> *cuerpo = new vector<Punto>;	//Vector cuerpo. 
    double V; 									//Velocidad
    int D; 										//Dirección hacia donde va, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
    Punto moverCabeza(); 						//genera una nueva posicion para la cabeza
    
};

#endif
