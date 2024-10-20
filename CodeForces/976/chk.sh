#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    clear
    printf "Running... (%d)\n" $tc
    python3 gen.py > inf
    ./a.out < inf > ouf
    ./test < inf > ans
    if !(diff ouf ans)
    then
        clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

