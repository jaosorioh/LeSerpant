#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "include/Tablero.h"
#include <unistd.h>
#include <curses.h>

using namespace std;

int main()
{
    int N = 30;
    int M = 30;

    srand(time(NULL));

    int npuntos = 1;
    Tablero t(&N, &M);
    
    initscr();
    
    noecho();
    cbreak();
    keypad(stdscr, true);
    clear();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    
    refresh();
    t.printGrid();
    
    for (int ch = getch(); ch != 'q'; ch = getch()) {
        t.update(ch);
        t.printGrid();
        
        //clrtoeol();
    }
    /*
        t.getPuntos()->clear();        
        t.randomXY(npuntos);
       // usleep(500000);*/
    

    endwin();

    return 0;
}
