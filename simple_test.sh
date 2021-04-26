#!/bin/bash

make clean
make

./ryohcc "6" > target.s

make target
./target
