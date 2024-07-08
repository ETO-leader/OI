#!/bin/bash
g++ B.cpp -Wall -O2
./a.out < io > out
echo result:
echo ----------differences----------
diff out stdout
