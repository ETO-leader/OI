#!/bin/bash
while true;do
    ./gen > io
    time ./a.out < io > out
    ./bf < io > stdout
    if !(diff out stdout);then
        exit 0
    else
        echo AC
    fi
done

