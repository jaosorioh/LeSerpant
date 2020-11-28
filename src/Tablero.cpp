#include "../include/Tablero.h"
#include <unistd.h>

using namespace std;

Tablero::Tablero()
{
    snake = new Serpiente();
    presas = new vector<Punto>;
    win = newwin(N + 2, M + 4, 4, 3);
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
        int m = static_cast<int>((M + 1) / 2.0);
        int y = rand() % (N) + 1;
        int x = 2 * (rand() % m + 1);

        if (getPuntoIndex(x, y, presas) == -1 && getPuntoIndex(x, y, snake->getCuerpo()) == -1) {
            Punto p(x, y);
            presas->push_back(p);
            i++;
        }
    }
}

void Tablero::printGameOver(bool pasaParedes)
{
    while(snake->getCuerpo()->size()>0)
    {
        snake->getCuerpo()->pop_back();
        usleep(0.5e4);
        printGrid(pasaParedes);
    }
    printBorder(2);
    string gover = "G A M E  O V E R";
    printMessage(gover);
    wrefresh(win);
    wclear(win);
   
}

void Tablero::printMessage(string & message)
{
    printBorder(2);
    wrefresh(win);
    wattron(win, COLOR_PAIR(1));
    
    int x = static_cast<int>(((M + 4) - message.length()) / 2.0);
    for (char& c : message) {
        mvwaddch(win, (N+2)/2, x, chtype(c));
        usleep(5e4);
        x++;
        wrefresh(win);
    }
    
}

string Tablero::readLine(string & message)
{
    printMessage(message);
    int x = static_cast<int>(((M + 4) - message.length()) / 2.0);
    int y = (N+2)/2;
    string line = readLine(y+1, (M+4)/2-8);
    wclear(win);
    return line;
}
string Tablero::readLine(int y, int x)
{
    string input;
    wattron(win, COLOR_PAIR(1));
    
    // let the terminal do the line editing

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();
    int i = 0;
    while ( true)
    {
        ch = getch();
    
        if(ch!=ERR )
        {
            if(ch=='\n' )
            {
                break;
            }
            else if (isalnum(ch)) {
                if(input.length()>8)
                {
                    break;
                }
                
                input.push_back( ch );
                
                mvwaddch(win, y, x, ch);
                wrefresh(win);
                x++;
            }
        } 
        
    }
    wclear(win);
    // restore your cbreak / echo settings here
    return input;
    /*
    printBorder();
    char str[10];
    wgetstr(win, str);
    usleep(1e5);
    mvprintw(2, 0, "You Entered: %s", str);
    return "";*/
    
}

void Tablero::printBorder(int color)
{
    
    wattron(win, COLOR_PAIR(color));
    
    for (int i = 0; i < M + 4; i++) {
        mvwaddch(win, 0, i, ' ');
        mvwaddch(win, N + 1, i, ' ');
    }
    
    for (int i = 1; i < N + 1; i++) {
        mvwaddch(win, i, 0, ' ');
        mvwaddch(win, i, 1, ' ');
        mvwaddch(win, i, M + 2, ' ');
        mvwaddch(win, i, M + 3, ' ');
    }   
}

void Tablero::printGrid(bool pasaParedes)
{
    int color = 2;
    if(pasaParedes==true)
    {
        color = 6;
    }
    
    printBorder(color);
    
    wattron(win, COLOR_PAIR(3));

    vector<Punto>* cuerpo_ = snake->getCuerpo();
    for (int i = 0; i < cuerpo_->size(); i++) {
        Punto* pa = &cuerpo_->at(i);
        mvwaddch(win, pa->getY(), pa->getX(), ' ');
        mvwaddch(win, pa->getY(), pa->getX() + 1, ' ');
    }
    
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
