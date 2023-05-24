#!/bin/bash

# printing out the sizes of all files in ascending order
# problem is that there are extraneous spaces everywhere
outa=$(ls -l | sort | cut -d$' ' -f8 -f9 -f10)
