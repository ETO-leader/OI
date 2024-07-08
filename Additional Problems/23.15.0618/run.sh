#!/bin/bash
if !(g++ D.cpp -Wall -O2);then
    echo CE: Compile Error
    exit 0
fi
echo -------used time-------
if !(time ./a.out < io > out);then
    echo RE: Runtime Error
    exit 0
fi
echo -------result-------
if diff out stdout;then
    echo AC: Accepted
else
    echo WA: Wrong Answer
fi
