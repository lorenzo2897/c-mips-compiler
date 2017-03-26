/* testing framework engine for unit tests */

#include <stdio.h>

int func(int a, int b, int c);

int main(int argc, char const *argv[]) {
	int a, b, c, obtained;

	if(argc < 4) {
		printf("input a b c via command line arguments\n");
		return 2;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);

	obtained = func(a, b, c);

	printf("(%d, %d, %d) => %d\n", a, b, c, obtained);
}
