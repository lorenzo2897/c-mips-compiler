#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void print_str(char* a) {
	printf("%s", a);
}

void print_int(int a) {
	printf("%d", a);
}

void print_uint(int a) {
	printf("%u", a);
}

void print_float(double a) {
	printf("%f", a);
}

void print_ptr(void* a) {
	printf("%p", a);
}


void scan_str(char* a) {
	scanf("%s", a);
}

void scan_int(int* a) {
	scanf("%d", a);
}

void scan_uint(unsigned* a) {
	scanf("%u", a);
}


void random_seed() {
	srand(time(NULL));
}

int random_get() {
	return rand();
}

double math_sqrt(double a) {
	return sqrt(a);
}
