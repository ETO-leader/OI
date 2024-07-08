#!/bin/bash
g++ E.cpp -Wall -O2
time ./a.out < io > ans
#g++ sol.cpp -O2 -o b.out && ./b.out < io > out
printf "%s" result:
echo 
printf "%s" ----------difference-----------
echo 
diff ans out
