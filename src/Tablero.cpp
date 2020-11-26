#include "../include/Tablero.h"
#include <unistd.h>

using namespace std;

Tablero::Tablero()
{
    snake = new Serpiente(N, M);
    presas = new vector<Punto>;
    win = newwin(N+2, M+4, 3, 3);
    wbkgd(win, COLOR_PAIR(1));    
    wrefresh(win);
}

Tablero::~Tablero()
{
    delete snake;
    delete presas;
    delete win;
}

Serpiente * Tablero::getSnake() const
{
    return snake;
}

void Tablero::setSnake(Serpiente *s)
{
    snake = s;
}

vector<Punto> * Tablero::getPresas() const
{
    return presas;
}

void Tablero::setPresas(vector<Punto> * presas_)
{
    presas = presas_;
}

int Tablero::getPuntoIndex(const int f, const int c, vector<Punto>* puntos)
{
    int i = 0;

    if (puntos->size() == 0)
        i = -1;
    else {
        for (; i < puntos->size(); i++) {
            Punto* p = &(puntos->at(i));

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
        int m = static_cast<int>((M - 2) / 2.0);
        int y = rand() % N + 1;
        int x = 2 * (rand() % m + 1);

        if (getPuntoIndex(x, y, presas) == -1 && getPuntoIndex(x, y, snake->getCuerpo()) == -1) {
            Punto p(x, y);
            presas->push_back(p);
            i++;
        }
    }
}

void Tablero::printGameOver()
{
    while(snake->getCuerpo()->size()>0)
    {
        snake->getCuerpo()->pop_back();
        usleep(1e4);
        printGrid();
    }
    wclear(win);
    printBorder();
    int n = static_cast<int>(N / 2.0);
    wattron(win, COLOR_PAIR(1));
    string toprint = "G A M E  O V E R";

    int m = static_cast<int>(((M + 2) - toprint.length()) / 2.0);
    
    for (char&c : toprint) {
        mvwaddch(win, n, m, chtype(c));
        wrefresh(win);
        m++;
        usleep(1e5);
    }
    usleep(1e6);
    wclear(win);
}

void Tablero::printBorder()
{
    wattron(win, COLOR_PAIR(2));
    for (int i = 0; i < N + 1; i++) {
        mvwaddch(win, i, 0, ' ');
        mvwaddch(win, i, 1, ' ');
        mvwaddch(win, i, M, ' ');
        mvwaddch(win, i, M + 1, ' ');
    }

    for (int i = 0; i < M + 2; i++) {
        mvwaddch(win, 0, i, ' ');
        mvwaddch(win, N + 1, i, ' ');
    }
}

void Tablero::printGrid()
{
    printBorder();
    wattron(win, COLOR_PAIR(3));

    vector<Punto>* cuerpo_ = snake->getCuerpo();
    for (int i = 0; i < cuerpo_->size(); i++) {
        Punto* pa = &cuerpo_->at(i);
        mvwaddch(win, pa->getY(), pa->getX(), ' ');
        mvwaddch(win, pa->getY(), pa->getX() + 1, ' ');
    }
    wrefresh(win);
    wattron(win, COLOR_PAIR(4));

    for (int i = 0; i < presas->size(); i++) {
        Punto* pa = &presas->at(i);
        mvwaddch(win, pa->getY(), pa->getX(), ' ');
        mvwaddch(win, pa->getY(), pa->getX() + 1, ' ');
    }

    wrefresh(win);
    double dt = 1e6 * 1 / snake->getV();
    usleep(dt);
    werase(win);
}
