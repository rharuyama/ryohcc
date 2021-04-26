#!/bin/bash

make clean
make

./ryohcc "46" > target.s

make target
./target
