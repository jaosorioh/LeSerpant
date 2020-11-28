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

    init_color(COLOR_RED, 650, 2, 2);
    init_color(30, 500, 500, 500);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    
    init_pair(6, COLOR_WHITE, 30);
    
    wbkgd(stdscr, COLOR_PAIR(1));
    
    Nivel nivel1(50, 1, true);
    Nivel nivel2(100, 2, false);
    Nivel nivel3(200, 3, false);
    niveles = {nivel1, nivel2, nivel3};
    nivel_actual = 0;
}

void Juego::jugar()
{
    bool gameFinished = false;
    string uname = "";
    while (true) {
        refresh();
        mainMenu();
        clear();
        erase();
        refresh();
        t = new Tablero();
        if(uname == "")
        {
            string message = "Ingrese su nick:";
            uname = t->readLine(message);
            player = new Jugador(uname);
            usleep(1e6);
        }
        
        int np = niveles[nivel_actual].getNPresas(); 
        t->randomXY(np);
        
        int ch = KEY_UP;
        
        string user = "Jugador: " + player->getName();
        mvprintw(1, 3, user.c_str());
        while (true) 
        {
            //imprime el puntaje y se actualiza
            string score = "Puntaje: " + to_string(player->getCurrScore());
            mvprintw(1, (M + 4) - score.length(), score.c_str());
            string nivel = "Nivel: " + to_string(nivel_actual+1);
            mvprintw(2, (M + 4) - nivel.length(), nivel.c_str());
            
            t->printGrid(niveles[nivel_actual].getpasaParedes());
            
            int aux_ch = getch();
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
                    }
                    gameFinished = update(ch);
                    
                }
                else
                {
                    gameFinished = update(ch);
                }
                    
            }
            //lo que hace una vez pierde
            if (gameFinished) 
            {
                usleep(0.6e4);
                clear();
                t->printGameOver(niveles[nivel_actual].getpasaParedes());
                usleep(1e6);

                player->checkMaxScore();
                player->setNewFile();
                player->setCurrScore(0);
                nivel_actual = 0;

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
    int ch = getch();
    if(ch!=ERR)
    {
        ch = 0;
    }
    while (true) {
        ch = getch();
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
    
    bool touchesWall = false;
    Punto newCabeza = snake->moverCabeza(ch, touchesWall);
    if(touchesWall && niveles[nivel_actual].getpasaParedes()==false)
    {
        gameFinished = true;
    }else{
    
        int index = t->getPuntoIndex(newCabeza.getX(), newCabeza.getY(), presas);
        if (index > -1) {
            presas->erase(presas->begin() + index);
            beep();
            player->addCurrScore(10); //suma puntos por comer

            snake->comer(newCabeza);
            int np = 1;
            //pasar de nivel
            if(player->getCurrScore()>=niveles[nivel_actual].getScore())
            {
                if(nivel_actual<niveles.size()-1)
                {
                    nivel_actual++;
                    t = new Tablero();
                    np = niveles[nivel_actual].getNPresas();
                }
            }
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
    }
    return gameFinished;
}
