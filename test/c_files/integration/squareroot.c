/* integer square root */

#include "../framework/integration_driver.h"

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
		print_str("please enter an integer: ");
		scan_uint(&in);
		x = my_sqrt(in);
		print_str("floor of square root: ");
		print_int(x);
		print_str("\n");
	}
	return 0;
}
