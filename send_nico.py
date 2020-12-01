#!/usr/bin/env python
import os
import sys

os.system("resize -s 32 64");
os.system( 'g++ -std=c++11 src/*.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')
