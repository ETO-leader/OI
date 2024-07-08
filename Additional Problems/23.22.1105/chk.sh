#!/bin/bash
declare -i tcase=1
while true;do
    printf "On testcase %d\n" $tcase
    ./gen 1000 200 > matrix.in
    time ./matrix
    if !(./ckr matrix.in matrix.out matrix.ans);then
        exit 0
    fi
    tcase=$tcase+1
done

