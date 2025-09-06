#!/bin/bash

declare -i tc=0

while ( true )
do
    tc=$tc+1
    printf "Running(%d)...\n" $tc
    pypy3 gen.py > sequence.in
    time ./sequence
    ./bf < sequence.in > sequence.ans
    if !(diff -w sequence.out sequence.ans)
    then
        printf "wa.\n"
        break
    fi
    printf "ok.\n"
done
