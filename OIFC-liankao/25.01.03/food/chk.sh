#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    clear
    printf "Running... (%d)\n" $tc
    python3 gen.py 50 50 > food.in
    ./food
    if !(./spj food.in food.out food.ans)
    then
        clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

