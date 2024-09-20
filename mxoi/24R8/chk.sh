#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    clear
    printf "Running... (%d)\n" $tc
    python3 gen.py > c.in
    ./c
    ./bfc
    if !(diff c.out c.ans)
    then
        clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

