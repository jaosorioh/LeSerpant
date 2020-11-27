#include "../include/Juego.h"
#include <unistd.h>

using namespace std;

Juego::Juego()
{
    
    srand(time(NULL));

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, TRUE);

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void Juego::jugar()
{
    bool gameFinished = false;
    while (true) {
        wbkgd(stdscr, COLOR_PAIR(1));
        refresh();
        mainMenu();
        clear();
        t = new Tablero();
        int np = 1;
        t->randomXY(np);
        int ch = KEY_UP;
        string user = "Jugador: brayanpapi";
        mvprintw(1, 3, user.c_str());
        string score = "Puntaje: 200";
        mvprintw(1, (M + 4) - score.length(), score.c_str());
        while (true) {
            t->printGrid();

            int aux_ch = getch();
            clrtoeol();
            if (aux_ch == ERR) {
                gameFinished = update(ch);
            }
            else if(aux_ch!=ERR){
                if(aux_ch == 27)
                {
                    erase();
                    endwin();
                    exit(0);
                }
                else if(aux_ch == ch)
                {
                    gameFinished = update(ch);
                }
                else if(aux_ch == KEY_UP || aux_ch == KEY_DOWN || aux_ch == KEY_LEFT || aux_ch == KEY_RIGHT)
                {
                    if ((ch == KEY_DOWN && aux_ch != KEY_UP) || (ch == KEY_UP && aux_ch != KEY_DOWN) || (ch == KEY_LEFT && aux_ch != KEY_RIGHT) || (ch == KEY_RIGHT && aux_ch != KEY_LEFT)) {
                    ch = aux_ch;
                    gameFinished = update(ch);
                    }
                }
                else
                {
                    gameFinished = update(ch);
                }
                    
            }
            if (gameFinished) {
                usleep(0.6e4);
                clear();
                t->printGameOver();
                usleep(1e6);
                break;
            }
        }
    }
    endwin();
}

void Juego::mainMenu()
{
    int i = 0;
    for (; i < snake_pxart.size(); i++) {
        for (int j = 0; j < snake_pxart.at(i).size(); j++) {
            attron(COLOR_PAIR(snake_pxart[i][j] + 1));
            mvprintw(i + 1, 2 * j + 5, " ");
            mvprintw(i + 1, 2 * j + 6, " ");
            usleep(0.6e4);
            refresh();
        }
    }

    attron(COLOR_PAIR(1));
    refresh();
    i += 2;
    for (int k = 0; k < toprint.size(); k++) {
        string str = toprint.at(k);
        int x = 5 + static_cast<int>((30 - str.length()) / 2.0);
        for (char& c : str) {
            mvaddch(i + k, x, chtype(c));
            refresh();
            usleep(1.2e4);
            x++;
        }
        if (k < 2 || k > 3)
            i++;
    }
    refresh();
    while (true) {
        int ch = getch();
        if (ch == 10) {
            break;
        }
        else if (ch == 27) {
            erase();
            endwin();
            exit(0);
        }
    }
}

bool Juego::update(int& ch)
{
    bool gameFinished = false;
    Serpiente* snake = t->getSnake();
    vector<Punto>* presas = t->getPresas();
    
    Punto newCabeza = snake->moverCabeza(ch);
    
    int index = t->getPuntoIndex(newCabeza.getX(), newCabeza.getY(), presas);
    if (index > -1) {
        presas->erase(presas->begin() + index);
        beep();
        snake->comer(newCabeza);
        int np = 1;
        t->randomXY(np);
        
    }
    else {
        int index = t->getPuntoIndex(newCabeza.getX(), newCabeza.getY(), snake->getCuerpo());
        if (index == -1 || (index == snake->getCuerpo()->size()-1 && snake->getCuerpo()->size() <= N)) {
            snake->moverse(ch);
        }
        else {
            gameFinished = true;
        }
    }        
    return gameFinished;
}