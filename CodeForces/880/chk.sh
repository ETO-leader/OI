#!/bin/bash

while ( true )
do
    pypy3 gen.py > inf
    time ./d < inf > ouf
    ./t < inf > ans
    if !(diff -w ouf ans)
    then
        printf "wa\n"
        break
    fi
done