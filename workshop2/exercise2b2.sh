#!/bin/bash

# we assume, very sluttily, that the parameter will always be a number. (I'm not sure we can even type check in bash so IDGAF)
number=$1 #super slutty IK
ls -l | sort -k 8n | head -n $number