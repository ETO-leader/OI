#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    clear
    printf "Running... (%d)\n" $tc
    pypy3 gen.py > battle.in
    time ./battle
    ./chk
    if !(diff battle.out battle.ans)
    then
        clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

