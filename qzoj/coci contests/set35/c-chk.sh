#!/bin/bash

while ( true )
do
    pypy3 c-gen.py
    time ./c < c-inf > c-ouf
    if !(diff -w c-ouf c-ans)
    then
        printf "wa."
        break
    fi
    printf "ok."
done
