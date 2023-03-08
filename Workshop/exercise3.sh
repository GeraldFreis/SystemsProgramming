#!/bin/bash/

echo "The files sorted in an ascending manner by file size is: "

ls -S -r

echo "and the associated sizes in bytes are: "

ls -S -r -l | tr -s ' ' | cut -d ' ' -f 5



