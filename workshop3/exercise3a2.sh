#!/bin/bash

for ((i=1; i < 5; i++));
do
	if [ $i -eq 1 ]
	then
		timestamp1=$(sed "${i}q;d" prac3.csv)
		echo $timestamp1
	else
		timestamp1=$(sed "${i}q;d" prac3.csv)
		timestamp2=$(sed "${i}q;d" prac4.csv)
		echo $timestamp1
		echo $timestamp2
	fi
done