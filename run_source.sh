#!/bin/bash

make clean
make

./ryohcc "$@" > target.s

make target
./target
