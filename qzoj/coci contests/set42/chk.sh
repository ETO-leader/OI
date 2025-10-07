#!/bin/bash

declare -i c=0

while (true)
do
    printf "Running(%d)...\n" $c
    c=$((c+1))
    pypy3 gen.py > inf
    time ./b < inf > ouf
    if !(./spj inf ouf ans)
    then
        break
    fi
done

