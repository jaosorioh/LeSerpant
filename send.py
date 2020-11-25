#!/usr/bin/env python
import os
import sys

os.system( 'g++ src/*.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')
