#!/bin/bash
while true;do
    ./gen 100 10000 > inf
    time ./a.out < inf > ouf
    ./chk < inf > ans
    if diff ouf ans;then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0
    fi
done
