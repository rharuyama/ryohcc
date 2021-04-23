#!/bin/bash

make clean
make

./.ryohcc "6 * 5 * 4" > target.s

make target
./.target
