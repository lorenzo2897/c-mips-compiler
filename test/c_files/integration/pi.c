/* calculating pi */

#include "../framework/integration_driver.h"

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
	int iterations = 5000000;
	int sum = 0;
	int i;
	double pi;

	random_seed();

	for(i = 0; i < iterations; i++) {
		int a, b;
		// calculate two random numbers
		a = random_get();
		b = random_get();
		// are they co-prime?
		if(coprime(a, b)) {
			sum++;
		}
	}

	// calculate pi

	pi = math_sqrt(6.0 / sum * iterations);

	print_str("pi ~= ");
	print_float(pi);
	print_str("\n");

	return 0;
}
