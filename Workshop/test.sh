#!/bin/bash

echo "Hello World"

cat "testText.txt"

echo "Now we will check how many files are in the current directory"


 declare -i counter=0

for FILE in *
do
	((counter=counter+1))
done

echo "The number of files in the current directory is: "
echo "$counter"

