#!/bin/bash

make clean
make

./ryohcc "6*5" > target.s

make target
./target
