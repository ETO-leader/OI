#!/bin/bash
while true;do
    ./d > io
    time ./a.out < io > out
    if ./chk io out stdout;then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0
    fi
done

