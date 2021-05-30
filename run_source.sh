#!/bin/bash

make clean
make

./ryohcc "$(cat source)" > target.s

make target
./target
