declare -i num=0

read num

if [ $num -lt 126 ]
then
    echo 4
elif [ $num -lt 212 ]
then
    echo 6
else
    echo 8
fi

