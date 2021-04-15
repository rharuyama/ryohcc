#!/bin/bash
set -e
echo "77" > source
make
./assem
# echo $?
