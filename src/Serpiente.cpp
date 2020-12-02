//Clase Serpiente

#include "../include/Serpiente.h"
using namespace std;

//Constructor. Condiciones iniciales:
Serpiente::Serpiente(int L, double V_)
{
    setV(V_);
    int n = static_cast<int>(N / 2.0);	//verificar
    int m = static_cast<int>(M / 2.0);
    if (n + L > N) {
        L = 3;
    }

    for (int i = 0; i < L; i++) {		//Añadir los L=3 elementos al cuerpo	
        Punto p(m, n + i);
        cuerpo->push_back(p);			//El cuerpo es un vector
    }
}

Serpiente::~Serpiente()		//Destructor
{
    delete cuerpo;
}

//Set V:
void Serpiente::setV(double V_)
{
    if(V_ < Vmin)		//Verificamos que el V ingresado sea válido (menor al máximo por nivel)
    {
        V_ = Vmin;
    }
    else if(V_ > Vmax)   //Si es mayor lo fijamos en el máximo
    {
        V_ = Vmax;
    }
    V = V_;
}

double Serpiente::getV() const
{
    return V;
}

//Aumentar velocidad: 
void Serpiente::modVel()
{
    setV(getV()+aum); //Seteamos la velocidad actual más el aumenta
}

//Set y get Dirección hacia donde va, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
void Serpiente::setD(int D_)
{
    D = D_;
}

int Serpiente::getD() const
{
    return D;
}

//Setear cuerpo
void Serpiente::setCuerpo(vector<Punto> *cuerpo_)
{
    cuerpo = cuerpo_;
}

vector<Punto> *Serpiente::getCuerpo()
{
    return cuerpo;
}

//Mover cabeza (y por ende la serpiente)
//INPUT: Recibe la dirección y un bool que nos dirá si se pueden atravezar las paredes o no
//Output: Un punto que será agruegado al principio del vector en cada movimiento.
Punto Serpiente::moverCabeza(int D_, bool &touchesWall)
{
	//Obtenemos las posiciones x,y de la posición 0 del cuerpo (vector de puntos)
    int x = cuerpo->at(0).getX();
    int y = cuerpo->at(0).getY();
	
	//Si Dirección es a la izquierda
    if (D_ == KEY_LEFT) {
        x -= 2; 		//Avanzamos 2 a la izquierda
        if(x<xmin)		//Verificamos que esté en el tablero
        {
            touchesWall = true;	//Pasa de un lado al otro
            x = M;
        }
    }

	//Dirección a la derecha
    if (D_ == KEY_RIGHT) {
        x+=2;			//2 a la derecha
        if(x > M)
        {
            touchesWall = true;
            x = xmin;
        }
    }

	//Abajo. Aquí la interfaz tiene el detalle de que está al revés, es decir, para abajo hay que sumar en Y y para arriba restar.
    if (D_ == KEY_DOWN) {
        y++;		//Avanzamos uno abajo. Es solo uno porque también la interfaz es más larga en y que en x. (el doble)
        if(y>N)
        {
            touchesWall = true;
            y = ymin;
        }
    }

	//Para arriba restamos 2 en y.
    if (D_ == KEY_UP) {
        y--;
        if(y<ymin)
        {
            touchesWall = true;
            y = N;
        }
    }

    Punto P(x, y);
    return P;
}

//Mover cabeza está sobrecargado, sin argumentos es la misma función pero con touchesWall = false
//INPUT: Nada
//Output: un punto, como en el moverCabeza anterior
Punto Serpiente::moverCabeza()
{
    bool touchesWall = false;
    return moverCabeza(D, touchesWall);
}

//Para hacer crecer la serpiente y aumentar la velocidad cuándo come
void Serpiente::comer(Punto &p)	//Recibe un punto nuevo
{
    cuerpo->insert(cuerpo->begin(), p);	//insertamos un nuevo punto en la cola
    modVel();
}

//Para moverse. Recibe un caracter (una flecha)
void Serpiente::moverse(int& ch)
{
    D = ch;										//Dirección es la flecha	
    bool touchesWall;							//touchesWall segun el nivel
    Punto cabeza = moverCabeza();				//Llamamos mover cabeza 
    cuerpo->insert(cuerpo->begin(), cabeza);	//Insertamos un nuevo punto en la cabeza
    cuerpo->pop_back();							//Borramos el punto de la cola para generar el movimiento.
}
