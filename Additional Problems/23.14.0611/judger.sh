#!/bin/bash
declare -i time_limit=2
for testcase in {1..10};do
    echo Testcase \# $testcase :
    ./d > io
    ./sol < io > stdout
    if !(timeout $time_limit ./a.out < io > out);then
        echo tle: Time Limited Exceed
        exit 0
    fi
    if !(./chk io out stdout);then
        echo State: Unaccepted
        exit 0
    fi
done
echo State: Accepted
