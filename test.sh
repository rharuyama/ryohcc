#!/bin/bash
set -e
echo " 7 * 5 /3" > source
make
./assem
# echo $?
