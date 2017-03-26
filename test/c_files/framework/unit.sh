#!/bin/bash

EXIT_CODE=0

# compile the test program

if [[ "$1" == "lscc" ]]; then
	cat test/c_files/unit/$2.c | cpp | bin/lscc -S -o test/out/asm/$2.s
	mips-linux-gnu-gcc -std=c90 -static test/c_files/framework/unit_driver.c test/out/asm/$2.s -o test/out/unit/$2
	if [[ $? -ne 0 ]]; then
		echo "Failed $2: program did not compile"
		exit 1
	fi
fi

if [[ "$1" == "debug" ]]; then
	cat test/c_files/unit/$2.c | cpp | bin/lscc -S -o test/out/asm/$2.s
	mips-linux-gnu-gcc -std=c90 -static test/c_files/framework/unit_debugger.c test/out/asm/$2.s -o test/out/unit/$2
	if [[ $? -ne 0 ]]; then
		echo "Failed to compile $2"
		exit 1
	fi
	echo "program located at test/out/unit/$2"
	exit 0
fi

if [[ "$1" == "gcc" ]]; then
	gcc -std=c90 -pedantic -S test/c_files/unit/$2.c -o test/out/asm/$2.s
	gcc -std=c90 test/c_files/framework/unit_driver.c test/out/asm/$2.s -o test/out/unit/$2
	if [[ $? -ne 0 ]]; then
		echo "Failed $2: program did not compile"
		exit 1
	fi
fi

if [[ "$1" == "dgcc" ]]; then
	gcc -std=c90 -pedantic -S test/c_files/unit/$2.c -o test/out/asm/$2.s
	gcc -std=c90 test/c_files/framework/unit_debugger.c test/out/asm/$2.s -o test/out/unit/$2
	if [[ $? -ne 0 ]]; then
		echo "Failed to compile $2"
		exit 1
	fi
	echo "program located at test/out/unit/$2"
	exit 0
fi


# run the test program for each test tuple
test_description=""
while read -r line || [[ -n "$line" ]]; do

	if [[ "$line" == \/\*d* ]]; then
		test_description="${line:4:-3}"
	fi

    if [[ "$line" == \/\*@* ]]; then
		parts=($line)
		test/out/unit/$2 ${parts[1]} ${parts[2]} ${parts[3]} ${parts[4]}
		if [[ "$?" -ne "0" ]]; then
			echo "Failed $2 ($test_description) for tuple (${parts[1]}, ${parts[2]}, ${parts[3]}) => ${parts[4]}"
			echo
			EXIT_CODE=1
		fi
	fi
done < "test/c_files/unit/$2.c"

exit $EXIT_CODE
