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
            if (aux_ch == ERR || aux_ch == ch) {
                gameFinished = update(ch);
            }
            else if (aux_ch == 27) {
                gameFinished = true;
            }
            else if ((ch == KEY_DOWN && aux_ch != KEY_UP) || (ch == KEY_UP && aux_ch != KEY_DOWN) || (ch == KEY_LEFT && aux_ch != KEY_RIGHT) || (ch == KEY_RIGHT && aux_ch != KEY_LEFT)) {
                ch = aux_ch;
                gameFinished = update(ch);
            }

            else {
                gameFinished = false;
            }

            if (gameFinished) {
                clear();
                t->printGameOver();
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
            usleep(0.7e4);
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
            usleep(0.6e5);
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
        int np = 1;
        t->randomXY(np);
        snake->moverse(true, ch);
    }
    else {
        int index = t->getPuntoIndex(newCabeza.getX(), newCabeza.getY(), snake->getCuerpo());
        if (index == -1) {
            snake->moverse(false, ch);
        }
        else {
            gameFinished = true;
        }
    }

    if (!gameFinished) {
        Punto* cabeza = &snake->getCuerpo()->at(0);

        if (cabeza->getX() < 2) {
            cabeza->setX(M - 2);
        }
        else if (cabeza->getX() > M - 2) {
            cabeza->setX(2);
        }
        else if (cabeza->getY() < 1) {
            cabeza->setY(N);
        }
        else if (cabeza->getY() > N) {
            cabeza->setY(1);
        }
    }
    return gameFinished;
}