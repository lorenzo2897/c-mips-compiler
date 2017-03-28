#!/bin/bash

cc=bin/lscc
if [[ $2 == "gcc" ]]; then
	cc="mips-linux-gnu-gcc -std=c90 -S -xc - -o -"
fi

bnx=$1
mkdir -p test/out/bin
cpp test/c_files/integration/$bnx.c | $cc > test/out/asm/$bnx.s || exit 1
mips-linux-gnu-gcc -std=c90 -static test/c_files/framework/integration_driver.c test/out/asm/$bnx.s -lm -o test/out/bin/$bnx && test/out/bin/$bnx
