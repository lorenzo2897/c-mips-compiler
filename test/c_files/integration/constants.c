/* constants and conversions */

#include "../framework/integration_driver.h"

int main() {
	char* x = "hey";
    int n = 6;
    float f1 = 2.4F;
    float f2 = 4.5;
    double d1 = 66.F;
    double d2 = 26.65363547654745680;
	int i;

    for(i = 0; i < 6; i++) {
		switch (i) {
			case 0:
				print_str(x);
				break;
			case 1:
				print_int(n);
				break;
			case 2:
				print_float(f1);
				break;
			case 3:
				print_float(f2);
				break;
			case 4:
				print_float(d1);
				break;
			case 5:
				print_float(d2);
				break;
		}
		print_str("\n");
    }
}
