//Clase Serpiente
#include "../include/Serpiente.h"
using namespace std;

//Initial conditions:
Serpiente::Serpiente(const int& N, const int& M, int L, double V_)
{
    setV(V_);
    int n = static_cast<int>(N / 2.0);//verificar
    int m = static_cast<int>(M / 2.0);
    if (n + L > N) {
        L = 3;
    }

    for (int i = 0; i < L; i++) {
        Punto p(m, n + i);
        cuerpo->push_back(p);
    }
}

void Serpiente::setV(double V_)
{
    V = V_;
}

double Serpiente::getV() const
{
    return V;
}

void Serpiente::setD(int D_)
{
    D = D_;
}

int Serpiente::getD() const
{
    return D;
}

void Serpiente::setCuerpo(vector<Punto> *cuerpo_)
{
    cuerpo = cuerpo_;
}

vector<Punto> *Serpiente::getCuerpo()
{
    return cuerpo;
}

Punto Serpiente::moverCabeza(int D_)
{
    //int tecla = getch();
    //if(tecla!=ERR){

    int x = cuerpo->at(0).getX();
    int y = cuerpo->at(0).getY();

    if (D_ == KEY_LEFT) {
        x-=2;
    }

    if (D_ == KEY_RIGHT) {
        x+=2;
    }

    if (D_ == KEY_DOWN) {
        y++;
    }

    if (D_ == KEY_UP) {
        y--;
    }

    Punto P(x, y);
    return P;
}

Punto Serpiente::moverCabeza()
{
    return moverCabeza(D);
}

void Serpiente::moverse(bool P, int& ch)
{
    D = ch;
    Punto cabeza = moverCabeza();
    cuerpo->insert(cuerpo->begin(), cabeza);
    if (!P) { //Para cuando coma.
        cuerpo->pop_back();
    }
}