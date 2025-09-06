#!/bin/bash

declare -i tc=0

while ( true )
do
    tc=$tc+1
    printf "Running(%d)...\n" $tc
    pypy3 gen.py > graph.in
    time ./graph
    ./qwq < graph.in > graph.ans
    if !(./spj graph.in graph.out graph.ans)
    then
        break
    fi
done
