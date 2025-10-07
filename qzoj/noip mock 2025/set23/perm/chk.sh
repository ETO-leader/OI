#!/bin/bash

while ( true )
do
    pypy3 gen.py > perm.in
    ./bf
    ./perm
    cat perm.out
    cat perm.ans
    echo ''
    if !(diff -w perm.out perm.ans)
    then
        break
    fi
done
