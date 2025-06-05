#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    printf "Running... (%d)\n" $tc
    pypy3 testgen.py > inf
    time ./silksong-11 < inf > ouf
    ./bf < inf > ans
    if !(diff -w ouf ans)
    then
        clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

