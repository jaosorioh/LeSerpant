//Clase Serpiente
#include "../include/Serpiente.h"
using namespace std;

//Initial conditions:
Serpiente::Serpiente(int L, double V_)
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

Serpiente::~Serpiente()
{
    delete cuerpo;
}
void Serpiente::setV(double V_)
{
    if(V_ < Vmin)
    {
        V_ = Vmin;
    }
    else if(V_ > Vmax)   
    {
        V_ = Vmax;
    }
    V = V_;
}

double Serpiente::getV() const
{
    return V;
}

void Serpiente::modVel()
{
    setV(getV()+aum);
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

Punto Serpiente::moverCabeza(int D_, bool &touchesWall)
{
    int x = cuerpo->at(0).getX();
    int y = cuerpo->at(0).getY();

    if (D_ == KEY_LEFT) {
        x -= 2;
        if(x<xmin)
        {
            touchesWall = true;
            x = M;
        }
    }

    if (D_ == KEY_RIGHT) {
        x+=2;
        if(x > M)
        {
            touchesWall = true;
            x = xmin;
        }
    }

    if (D_ == KEY_DOWN) {
        y++;
        if(y>N)
        {
            touchesWall = true;
            y = ymin;
        }
    }

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

Punto Serpiente::moverCabeza()
{
    bool touchesWall = false;
    return moverCabeza(D, touchesWall);
}

void Serpiente::comer(Punto &p)
{
    cuerpo->insert(cuerpo->begin(), p);
    modVel();
}

void Serpiente::moverse(int& ch)
{
    D = ch;
    bool touchesWall;
    Punto cabeza = moverCabeza();
    cuerpo->insert(cuerpo->begin(), cabeza);
    cuerpo->pop_back();
}