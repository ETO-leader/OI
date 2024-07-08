#!/bin/bash
while true;do
    ./gen 10 > inf
    time ./a.out < inf > ouf
    ./ckr < inf > ans
    if diff ouf ans;then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0
    fi
done
