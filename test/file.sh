#!/bin/bash

bnx=$1
mkdir -p test/out/bin
cat test/c_files/integration/$bnx.c | cpp | bin/lscc -S -o test/out/asm/$bnx.s || exit 1
mips-linux-gnu-gcc -std=c90 -static test/c_files/framework/integration_driver.c test/out/asm/$bnx.s -o test/out/bin/$bnx && test/out/bin/$bnx
