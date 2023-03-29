#!/bin/bash

gcc q3.c -o q3out

rm outfile3.txt
touch outfile3.txt
for ((i=0; i < 10; i++))
do
    start=$(date +%s);
    ./q3out marks1.csv marks2.csv
    end=$(date +%s);
    time=$end-$start;
    echo $time >> outfile3.txt
done