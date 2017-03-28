#!/bin/bash

mips-linux-gnu-gcc -c -S -x c - -o -
exit $?
