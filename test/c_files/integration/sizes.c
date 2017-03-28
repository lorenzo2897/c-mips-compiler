
#include "../framework/integration_driver.h"

int main() {
	char a;
	short b;
	int c;
	long d;
	float f;
	double g;
	long double h;

	print_str("char ");
	print_int(sizeof(a));
	print_str("\nshort ");
	print_int(sizeof(b));
	print_str("\nint ");
	print_int(sizeof(c));
	print_str("\nlong ");
	print_int(sizeof(d));
	print_str("\nfloat ");
	print_int(sizeof(f));
	print_str("\ndouble ");
	print_int(sizeof(g));
	print_str("\nlong dbl ");
	print_int(sizeof(h));
	print_str("\n");
}
