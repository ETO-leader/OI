#!/bin/bash

declare -i tc=0

while (true)
do
    tc=$tc+1
    # clear
    printf "Running... (%d)\n" $tc
    python3 chk.py > inf
    if !(cat inf | python3 testing-tool.py ./a.out)
    then
        # clear
        printf "wrong answer on test %d\n" $tc
        exit 0
    fi
done

