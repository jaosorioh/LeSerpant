//Clase Serpiente

#include "../include/Serpiente.h"

using namespace std;

//Initial conditions:
Serpiente::Serpiente(int L_ = 3, double V_ = 0.01){
    setV(V_);
}

Serpiente::Serpiente(){
    int L_;
    double V_;
    
    setV(V_);
}



void Serpiente::setV(double V_) {
    V = V_;
}

double Serpiente::getV() const {
    return V;
}

void Serpiente::Posicion(bool P){
	Punto NewPos = Serpiente::moverse();
	cuerpo.insert(cuerpo.begin(), NewPos);
	if(P == false){			//Para cuando coma.
		cuerpo.pop_back();}
}

void Serpiente::flechas(){
	int tecla = getch();
     if(tecla!=ERR){
            switch(tecla){
               case KEY_UP:    if(direccion != 1) direccion = 0; break;
               case KEY_DOWN:     if(direccion != 0) direccion = 1; break;
               case KEY_LEFT: if(direccion != 3) direccion = 2; break;
               case KEY_RIGHT:   if(direccion != 2) direccion = 3; break;
            		}
     		}
}

Punto Serpiente::moverse(){
	int x = cuerpo[0].getX();
	int y = cuerpo[0].getY();
	if(direccion == 0){ y--;}	//Arriba
	else if(direccion == 1){y++;}	//Abajo
	else if(direccion == 2){x--;}	//Izquierda
	else if(direccion == 3){x++;}	//Derecha
	Punto P(x, y);
	return P;
}
