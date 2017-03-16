/* testing framework engine for unit tests */

int func(int a, int b, int c);

int main(int argc, char const *argv[]) {
	int a, b, c, expected, obtained;

	if(argc < 5) {
		return 2;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
	expected = atoi(argv[4]);

	obtained = func(a, b, c);

	if(expected == obtained) {
		return 0; /* pass */
	} else {
		return 1; /* fail */
	}
}
