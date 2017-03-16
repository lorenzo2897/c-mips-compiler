#!/bin/bash

EXIT_CODE=0

# compile the test program

if [[ "$1" == "lscc" ]]; then
	cat test/c_files/unit/$2.c | cpp | bin/lscc -S -o test/out/asm/$2.s
fi

if [[ "$1" == "gcc" ]]; then
	gcc -std=c90 -pedantic -S test/c_files/unit/$2.c -o test/out/asm/$2.s
fi

gcc -std=c90 test/c_files/framework/unit_driver.c test/out/asm/$2.s -o test/out/unit/$2

# run the test program for each test tuple
while read -r line || [[ -n "$line" ]]; do
    if [[ "$line" == \/\*@* ]]; then
		parts=($line)
		test/out/unit/$2 ${parts[1]} ${parts[2]} ${parts[3]} ${parts[4]}
		if [[ "$?" -ne "0" ]]; then
			echo "Failed $2 for tuple (${parts[1]}, ${parts[2]}, ${parts[3]}) => ${parts[4]}"
			echo
			EXIT_CODE=1
		fi
	fi
done < "test/c_files/unit/$2.c"

exit $EXIT_CODE
