#!/usr/bin/env python
import os
import sys

os.system( 'g++ -std=c++11 src/Tablero.cpp src/Serpiente.cpp src/Punto.cpp src/Jugador.cpp src/Juego.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')
