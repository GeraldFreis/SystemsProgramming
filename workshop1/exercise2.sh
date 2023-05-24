#!/bin/bash

# sorting each file
rm tempfile.txt
touch tempfile.txt
cat file1.txt > tempfile.txt
# echo "" > tempfile.txt
cat file2.txt >> tempfile.txt

sort -a tempfile.txt | head -n 3 
# this will work on linux but not mac because mac locale environment variable is set up to not gaf