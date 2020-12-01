#include "../include/Tablero.h"
#include <unistd.h>

using namespace std;

Tablero::Tablero()
{
    //color personalizado para cuando se puede cruzar paredes
    init_color(COLOR_GRAY, 500, 500, 500);
    init_pair(6, COLOR_WHITE, 30);

    snake = new Serpiente();
    presas = new vector<Punto>;
    bricks = new vector<Punto>;
    //dibujo del tablero NXM en el centro, el +2 y +4 simboliza los bordes que debieron dibujarse.

    int termH;
    int termW;
    getmaxyx(stdscr, termH, termW);
    win = newwin(N + 2, M + 4, 5, (termW - (M + 4)) / 2);
    //se pinta el tablero de blanco
    wbkgd(win, COLOR_PAIR(1));
    //se actualiza la pantalla
    wrefresh(win);
}

//destructor, elimina los apuntadores
Tablero::~Tablero()
{
    delete snake;
    delete presas;
    delete win;
    delete bricks;
}

void Tablero::setSnake(Serpiente* s)
{
    snake = s;
}

Serpiente* Tablero::getSnake() const
{
    return snake;
}

void Tablero::setPresas(vector<Punto>* presas_)
{
    presas = presas_;
}

vector<Punto>* Tablero::getPresas() const
{
    return presas;
}

void Tablero::setBricks(vector<Punto>* bricks_)
{
    bricks = bricks_;
}

vector<Punto>* Tablero::getBricks() const
{
    return bricks;
}

//metodo que busca si el punto, representado por una fila y columna, existe en el vector dado
int Tablero::getPuntoIndex(const int f, const int c, vector<Punto>* puntos)
{
    int i = 0;

    //si el vector es vacio, no esta el punto agregado
    if (puntos->size() == 0)
        i = -1;
    else {
        //busca si el vector tiene un tamño mayor que 1
        for (; i < puntos->size(); i++) {
            Punto* p = &(puntos->at(i));
            //compara si el punto coincide con alguno de los del vector dado
            if ((p->getX() == f) && (p->getY() == c)) {
                break;
            }
        }
        //si se termina el loop anterior, quiere decir que no encontro
        if (i == puntos->size()) {
            i = -1;
        }
    }
    return i;
}

//metodo que genera n presas aleatorias

void Tablero::randomXY(int& npuntos, vector<Punto> *puntos)
{
    int i = 0;
    while (i < npuntos) {
        int m = static_cast<int>((M + 1) / 2.0);
        //genera coordenadas x, y aleatorias
        int y = rand() % (N) + 1;
        int x = 2 * (rand() % m + 1);

        //valida que ya no esten agregadas
        if (getPuntoIndex(x, y, presas) == -1 && getPuntoIndex(x, y, snake->getCuerpo()) == -1 && getPuntoIndex(x, y, bricks) == -1) {
            //se crea la presa
            Punto p(x, y);
            puntos->push_back(p);
            i++;
        }
    }
}

void Tablero::printBorder(int color)
{
    //se cambia el color segun el dado
    wattron(win, COLOR_PAIR(color));

    //borde horizontal
    for (int i = 0; i < M + 4; i++) {
        mvwaddch(win, 0, i, ' ');
        mvwaddch(win, N + 1, i, ' ');
    }

    //borde vertical
    for (int i = 1; i < N + 1; i++) {
        mvwprintw(win, i, 0, "  ");
        mvwprintw(win, i, M + 2, "  ");
    }
}

void Tablero::printGrid(bool pasaParedes)
{
    //2 es color gris, 6 es color negro
    int color = (pasaParedes) ? 6 : 2;

    //imprime el borde del color dado
    printBorder(color);

    //utiliza el color verde para la serpiente
    wattron(win, COLOR_PAIR(3));

    //dibuja la serpiente
    vector<Punto>* cuerpo_ = snake->getCuerpo();

    for (int i = 0; i < cuerpo_->size(); i++) {
        Punto* pa = &cuerpo_->at(i);
        mvwprintw(win, pa->getY(), pa->getX(), "  ");
    }

    //utiliza rojo para la presa
    wattron(win, COLOR_PAIR(4));

    for (int i = 0; i < presas->size(); i++) {
        Punto* pa = &presas->at(i);
        mvwprintw(win, pa->getY(), pa->getX(), "  ");
    }
    
    wattron(win, COLOR_PAIR(2));
    
    for (int i = 0; i < bricks->size(); i++) {
        Punto* pa = &bricks->at(i);
        mvwprintw(win, pa->getY(), pa->getX(), "  ");
    }
    //actualiza los cambios
    
    wrefresh(win);
    //modifica el tiempo de espera en que se mueve la culebra segun la velocidad
    double dt = 1e6 * 1 / snake->getV();
    //se genera un temporizador
    usleep(dt);
    //se borra el tablero despues de mostrarse, esto se hace porque printGrid esta en un loop
    werase(win);
}

void Tablero::printMessage(string& message)
{
    //para imprimir bordes, usamos negro
    printBorder(2);
    wrefresh(win);
    //usamos color negro para la letra
    wattron(win, COLOR_PAIR(1));

    //el mensaje lo imprimiremos en el centro
    int x = static_cast<int>(((M + 4) - message.length()) / 2);

    for (char& c : message) {
        mvwaddch(win, (N + 1) / 2, x, chtype(c));
        //tiempo de espera entre la impresion de cada caracter
        usleep(4 * WAIT_TIME);
        x++;
        wrefresh(win);
    }
}

//metodo que lee los caracteres enviados por pantalla y los muestra en la fila y columna especificada
string Tablero::readLine(int y, int x)
{
    //cadena a retornar
    string input;
    //utilizamos color negro para letra
    wattron(win, COLOR_PAIR(1));
    //variable para leer char;
    int ch = getch();

    while (true) {
        ch = getch();
        //validamos que se haya presionado una tecla
        if (ch != ERR) {
            //validamos que se presione ENTER
            if (ch == '\n' && input.size() > 0) {
                break;
            } //solo leemos caracteres alphanumericos
            else if(ch == KEY_BACKSPACE)
            {
                if(input.size()>0)
                {
                    x--;
                    mvwaddch(win, y, x, ' ');
                    input.pop_back();
                    wrefresh(win);
                }
                
            }
            else if (isalnum(ch) && input.length() <= MAX_CHAR) 
            {
                //mostramos el caracter
                ch = toupper(ch);
                mvwaddch(win, y, x, ch);
                wrefresh(win);
                //almacenamos el caracter
                input.push_back(ch);
                //aumentamos de columna
                x++;
            }
        }
    }
    //limpiamos despues de mostrar
    wclear(win);
    return input;
}

//metodo que lee una cadena de texto e imprime un mensaje
string Tablero::readLine(string& message)
{
    printMessage(message);
    //mostraremos lo que leemos en la mitad del ancho y mas abajo que el mensaje
    return readLine((N + 1) / 2 + 1, (M + 2 - MAX_CHAR) / 2);
}

//metodo que imprime el mensaje de game over y desvanece cuelbra
void Tablero::printGameOver(bool pasaParedes)
{
    //se va eliminando la culebra, desde la cola hasta la cabeza
    while (snake->getCuerpo()->size() > 0) {
        snake->getCuerpo()->pop_back();
        usleep(WAIT_TIME);
        //se actualiza la cuelebra sin la parte que se elimina
        printGrid(pasaParedes);
    }
    //se imprime un borde negro

    printBorder(2);
    string gover = "G A M E  O V E R";
    printMessage(gover);
    wrefresh(win);
    wclear(win);
}