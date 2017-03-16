#!/bin/bash

if [ -z "$1" ]
then
	echo "NOTE:"
    echo "If you would like to use gcc instead of lscc to compile test cases,"
	echo "specify 'gcc' as \$1"
	echo
	cmd=lscc
else
	cmd=$1
fi

if [[ "$cmd" == "clean" ]]; then
	echo "Cleaning output directories..."
	mkdir -p test/out/unit
	mkdir -p test/out/asm
	rm -f test/out/asm/*
	rm -f test/out/unit/*
	echo "Done :)"
	exit
fi

# check pre-requisites

if [ ! -f bin/lscc ]; then
    echo "bin/lscc not found!"
	exit 1
fi

# prepare directories

mkdir -p test/out/unit
mkdir -p test/out/asm

rm -f test/out/asm/*
rm -f test/out/unit/*

# run test/c_files/framework/unit.sh for each file in c_files/unit/

PASSED=0
TOTAL=0

for f in test/c_files/unit/*.c
do
	b=$(basename $f)
	testname=${b%.*}
	test/c_files/framework/unit.sh $cmd $testname
	if [[ "$?" -eq "0" ]]; then
		((PASSED++))
		echo "Passed all tuples for $testname"
	fi
	((TOTAL++))
done

# output summary

echo
echo "Passed $PASSED out of $TOTAL unit tests"

if [[ $PASSED -eq $TOTAL ]]; then
	exit 0
else
	exit 1
fi
