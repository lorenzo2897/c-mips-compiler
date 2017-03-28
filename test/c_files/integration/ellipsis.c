
#include "../framework/integration_driver.h"

int main() {
	char s[100];
	char readonly[10];

	printf("testing decimal %d and hex %X and unsigned %u and float %f\n", -543, 0xdeadbeef, -2, 1.2345);
	printf("testing %d %d float %f and %f\n", 1, 1, 1.234f, 6.78f);

	printf("input a string > ");
	scanf("%s", s);
	printf("you wrote %s\n", s);

	readonly = "yo";
	printf("\n%s\n", readonly);
}
