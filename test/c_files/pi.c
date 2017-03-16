/* calculating pi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int gcd(int a, int b) {
  int c;
  while (a != 0) {
     c = a;
	 a = b % a;
	 b = c;
  }
  return b;
}

int coprime(int a, int b) {
	return gcd(a, b) == 1;
}

int main(int argc, char const *argv[]) {
	int iterations = 10000000;
	int sum = 0;
	int i;
	double pi;

	srand(time(NULL));

	for(i = 0; i < iterations; i++) {
		int a, b;
		// calculate two random numbers
		a = rand();
		b = rand();
		// are they co-prime?
		if(coprime(a, b)) {
			sum++;
		}
	}

	// calculate pi

	pi = sqrt(6.0 / sum * iterations);

	printf("%f\n", pi);
}
