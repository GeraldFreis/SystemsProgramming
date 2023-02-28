#!/bin/bash/

#The goal is to take the top 3 alphabetical lines of the combination of f1 and f2

#First I will add f1 to f2, then sort, then print head 3

rm sorted.txt
touch sorted.txt

cat f1.txt >> sorted.txt
cat f2.txt >> sorted.txt

sort -d -f sorted.txt > output.txt

head -n 3 "output.txt"

