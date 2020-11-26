#include "include/Tablero.h"
#include <unistd.h>
#include <curses.h>

using namespace std;

int main()
{    
    int N = 20;
    int M = 2*N;
    
    srand(time(NULL));
    Tablero t(N, M);
    
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, TRUE);
    
    WINDOW *win = newwin(N+2, M+4, 3, 3);
    string user = "Jugador: brayanpapi";
    mvprintw(1, 3, user.c_str());
    string score = "Puntaje: 200";
    mvprintw(1, (M+4)-score.length(), score.c_str());
    
    start_color();
    

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    wbkgd(win, COLOR_PAIR(1));
    wrefresh(win);
    int ch = KEY_UP;    
    
    while (true) {
        bool gameFinished = t.update(ch);
        t.printGrid(win);
        if(gameFinished)
        {
            t.printGameOver(win); 
            break;
        }
        else
        {                
            int aux_ch = getch();
            if (aux_ch != ERR && aux_ch != ch) {
                if ((ch == KEY_DOWN && aux_ch != KEY_UP) || (ch == KEY_UP && aux_ch != KEY_DOWN) || (ch == KEY_LEFT && aux_ch != KEY_RIGHT) || (ch == KEY_RIGHT && aux_ch != KEY_LEFT)){
                    ch = aux_ch;
                }
            }
        }
    }

    endwin();   
    
    return 0;
}
