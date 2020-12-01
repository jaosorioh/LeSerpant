#!/usr/bin/env python

import os
import sys

os.system("resize -s 32 64");
os.system( 'g++ src/*.cpp Main.cpp -o a.out -lncurses')
os.system( './a.out')

