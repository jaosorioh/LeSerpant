#!/usr/bin/env python
import os
import sys

os.system( 'g++ src/Tablero.cpp src/Serpiente.cpp src/Punto.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')
