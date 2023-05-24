#!/bin/bash

# finding out how many files are in the current directory
a=$(ls | wc | awk '{print $1}')
echo "There are " $a " files in the current directory"

# another solution
counter=0
for row in $(ls)
do
	((counter=counter+1))
done
echo "There are " $counter " files in the current directory"
