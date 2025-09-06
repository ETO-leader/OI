#!/bin/bash

while ( true )
do
    pypy3 b-gen.py
    time ./b < b-inf > b-ouf
    if !(diff -w b-ouf b-ans)
    then
        printf "wa."
        break
    fi
    printf "ok."
done
