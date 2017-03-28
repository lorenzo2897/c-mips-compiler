#!/bin/bash

bnx=$1
mkdir -p test/out/bin
cpp test/c_files/integration/$bnx.c | bin/lscc -S -o test/out/asm/$bnx.s || exit 1
mips-linux-gnu-gcc -std=c90 -static test/c_files/framework/integration_driver.c test/out/asm/$bnx.s -lm -o test/out/bin/$bnx && test/out/bin/$bnx
