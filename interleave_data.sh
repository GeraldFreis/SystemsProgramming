#!/bin/bash
rm outfile2.txt
touch outfile2.txt

n1=$(wc -l $1);

for ((i=2; i <= 4; i++))
do
    time1=$(sed -n "${i}p" < $1);
    time2=$(sed -n "${i}p" < $2);
    
    timenum1=${time1:4:1};
    timenum2=${time2:4:1};
    # echo $timenum1
    # echo $timenum2
    if ((timenum1 < timenum2))
    then
        echo $time1 >> outfile2.txt
        echo $time2 >> outfile2.txt
    elif (( $timenum1 == $timenum2 ))
    then
        echo $time2 >> outfile2.txt
    else
        echo $time2 >> outfile2.txt
        echo $time1 >> outfile2.txt
    fi
    echo $time1 >> outfile2.txt
    echo $time2 >> outfile2.txt
done