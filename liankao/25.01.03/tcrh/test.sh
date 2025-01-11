declare -i score=0

for i in {0..20}
do
    cp tcrh$i.in tcrh.in
    timeout 1 ./tcrh
    if (diff -w tcrh.out tcrh$i.ans >> log)
    then
        if (($i > 0))
        then
            score=$score+5
        fi
        printf "Case %d: ac.\n" $i
    else
        printf "Case %d: unac.\n" $i
    fi
done