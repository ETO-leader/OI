#!/bin/bash

declare -i c=0

while (true)
do
    printf "Running(%d)...\n" $c
    c=$((c+1))
    pypy3 gen.py > inf
    time ./tmp < inf > ouf
    ./bf < inf > ans
    if !(diff -w ouf ans)
    then
        break
    fi
done

