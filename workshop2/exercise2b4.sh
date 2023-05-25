#!/bin/bash

#this is kinda fucking difficult this one
sum=0 # this wil hold the sum like a slut
# echo $1
# grep -e $1
for i in $*; do
	((sum=$sum+$(ls -l | grep -e $i | awk '{print $5}')))
done

echo $sum