#!/bin/bash

declare -i c=0

while ( true )
do
    c=$((c+1))
    printf "Running(%d)...\n" $c
    pypy3 gen.py --mode random --N 12 --cols 20 --max_ops 30 --seed 42 > grid.in
    pypy3 bf.py < grid.in > grid.ans
    time ./grid
    if !(./chk grid.in grid.out grid.ans)
    then
        break
    fi
done
