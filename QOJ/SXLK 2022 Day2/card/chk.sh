#!/bin/bash

declare -i Tcase=0

while ( true )
do
    clear
    Tcase=$Tcase+1
    printf "Running(%d)...\n" $Tcase
    pypy3 gen.py CHECK > inf
    ./card < inf > ouf
    ./chk  < inf > ans
    if !(diff -w ouf ans)
    then
        printf "wa.\n"
        break
    fi
    printf "ok.\n"
done
