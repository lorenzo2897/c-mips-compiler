/* integer square root */

#include <stdio.h>

unsigned my_sqrt(unsigned x) {
	unsigned root = 1, square = 1;
	while(x >= square) {
		root++;
		square = root * root;
	}

	return root - 1;
}

int main(int argc, char const *argv[]) {
	for(;;) {
		unsigned x, in;
		printf("please enter an integer: ");
		scanf("%u", &in);
		x = my_sqrt(in);
		printf("floor of square root: %d\n", x);
	}
	return 0;
}
