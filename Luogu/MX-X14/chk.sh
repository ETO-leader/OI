#!/bin/bash

declare -i tc=0

ulimit -s 524288

while (true)
do
    tc=$tc+1
    printf "Running... (%d)\n" $tc
    pypy3 gen.py > inf
    ./c < inf > ouf
    ./test < inf > ans
    if !(diff -w ouf ans)
    then
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

