#!/usr/bin/env python
import os
import sys

os.system( 'g++ -std=c++11 src/*.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')
