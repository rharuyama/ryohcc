#!/bin/bash
set -e
echo "4" > source
make
./assem
# echo $?
