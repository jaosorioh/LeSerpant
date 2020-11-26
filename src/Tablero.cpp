#include "../include/Tablero.h"
#include <unistd.h>
using namespace std;

Tablero::Tablero(int& N_, int& M_)
{
    N = N_;
    M = M_;
    snake = new Serpiente(N, M, 3, 15.0);
    presas = new vector<Punto>;
    int r = 1;
    randomXY(r);
}

void Tablero::setN(int& N_)
{
    N = N_;
}

int Tablero::getN() const
{
    return N;
}

void Tablero::setM(int & M_)
{
    M = M_;
}

int Tablero::getM() const
{
    return M;
}
/*
void Tablero::setPuntos(vector<Punto>* puntos_)
{
    puntos = puntos_;
}

vector<Punto>* Tablero::getPuntos() const
{
    return puntos;
}*/

int Tablero::getPuntoIndex(const int f, const int c, vector<Punto> *puntos)
{
    int i = 0;

    if (puntos->size() == 0)
        i = -1;
    else {
        for (; i < puntos->size(); i++) {
            Punto *p = &(puntos->at(i));

            if ((p->getX() == f) && (p->getY() == c)) {
                break;
            }
        }
        if (i == puntos->size()) {
            i = -1;
        }
    }
    return i;
}

void Tablero::randomXY(int& npuntos)
{
    int i = 0;

    while (i < npuntos) {
        int m = static_cast<int>((M-2) / 2.0);
        int y = rand() % N + 1;
        int x = 2*(rand() % m + 1);
        
        if (getPuntoIndex(x, y, presas) == -1 && getPuntoIndex(x, y, snake->getCuerpo())== -1) {
            Punto p(x, y);
            presas->push_back(p);
            i++;
        }
    }
}

bool Tablero::update(int& ch)
{
    bool gameFinished = false;
    Punto newCabeza = snake->moverCabeza(ch);
    int index = getPuntoIndex(newCabeza.getX(), newCabeza.getY(), presas);
    if(index>-1)
    {
        presas->erase(presas->begin() + index);
        int np = 1;
        randomXY(np);        
        snake->moverse(true, ch);
    }
    else
    {
        int index = getPuntoIndex(newCabeza.getX(), newCabeza.getY(), snake->getCuerpo());
        if(index == -1)
        {
            snake->moverse(false, ch);
        }
        else
        {
            gameFinished = true;
        }
        
    }    
    
    if(!gameFinished)
    {
        Punto *cabeza = &snake->getCuerpo()->at(0);

        if(cabeza->getX()<2)
        {
            cabeza->setX(M-2);
        }
        else if(cabeza->getX()>M-2)
        {
            cabeza->setX(2);
        }
        else if(cabeza->getY()<1)
        {
            cabeza->setY(N);
        }
        else if(cabeza->getY()>N)
        {
            cabeza->setY(1);
        }
        
    }
    return gameFinished;
    
}

void Tablero::printGameOver(WINDOW * win)
{
    werase(win);
    printBorder(win);
    int n = static_cast<int>(N / 2.0);
    wattron(win, COLOR_PAIR(1));
    string fullstring = "G A M E  O V E R";
    vector<string> toprint = {"G ","A ", "M ", "E  ", "O ","V ","E ","R"};
    
    int m = static_cast<int>(((M+2)-fullstring.length()) / 2.0);
    for(int i = 0; i<toprint.size(); i++)
    {
        mvwprintw(win, n, m+i*2, toprint[i].c_str() );
        wrefresh(win);
        usleep(0.25e6);
    }
    usleep(1e6);    
    
}

void Tablero::printBorder(WINDOW * win)
{
    wattron(win, COLOR_PAIR(3));
    for (int i = 0; i < N + 1; i++) {     
        mvwaddch(win, i, 0, ' ');
        mvwaddch(win, i, 1, ' '); 
        mvwaddch(win, i, M, ' ');
        mvwaddch(win, i, M + 1, ' ');   
    }
    
    for (int i = 0; i < M + 2; i++) {     
        mvwaddch(win, 0, i, ' ');
        mvwaddch(win, N+1, i, ' ');   
    }
}

void Tablero::printGrid(WINDOW * win)
{
    printBorder(win);
    wattron(win, COLOR_PAIR(2));
    
    vector<Punto>* cuerpo_ = snake->getCuerpo();
    for (int i = 0; i < cuerpo_->size(); i++) {
        Punto* pa = &cuerpo_->at(i);        
        mvwaddch(win, pa->getY(), pa->getX(), ' ');
        mvwaddch(win, pa->getY(), pa->getX()+1, ' ');         
    }
    
    wattron(win, COLOR_PAIR(4));
    
    for (int i = 0; i < presas->size(); i++) {
        Punto* pa = &presas->at(i);        
        mvwaddch(win, pa->getY(), pa->getX(), ' ');
        mvwaddch(win, pa->getY(), pa->getX()+1, ' ');         
    }
    
    wrefresh(win);
    double dt = 1e6*1/snake->getV();
    usleep(dt);
    werase(win);
}
