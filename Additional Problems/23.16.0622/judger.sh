#!/bin/bash
while true;do
    ./d > io
    ./r < io > out
    ./sol < io > stdout
    if !(./chk io out stdout);then
        exit 0
    fi
done
