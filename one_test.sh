#!/bin/bash

make clean
make

./ryohcc "a = 4;" > target.s

make target
./target
