/* fibonacci series */

#include "../framework/integration_driver.h"

int fib(int n) {
	if(n == 0) {
		return 1;
	} else if(n == 1) {
		return 1;
	} else {
		return fib(n-1) + fib(n-2);
	}
}

int main(int argc, char const *argv[]) {
	int i;
	for (i = 0; i < 20; i++) {
		int f = fib(i);
		print_int(f);
		print_str(" ");
	}
	return 0;
}
