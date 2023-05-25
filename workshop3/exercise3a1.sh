#!/bin/bash

# dude the song im listening to is so queefable fuckkk
#devil on my back by Chrissy. Im talking to a chick who is just so hot and so mentally Ill. Can't end well but shes stabbed 5 people so cant be too bad
rm outfile1.txt
touch outfile1.txt # i store it here
counter=0
for i in $(cat prac1.csv); do
	fullstring=$i
	name=$(cut -d$',' -f1 <<< $i)
	# echo $name
	examgrade=$(cat prac2.csv | grep -e $name | cut -d$',' -f2)
	if [ $examgrade ]
	then
		echo $fullstring,$examgrade
	else
		echo $fullstring,-
	fi
done
