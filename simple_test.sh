#!/bin/bash

make clean
make

./ryohcc "32" > target.s

make target
./target
