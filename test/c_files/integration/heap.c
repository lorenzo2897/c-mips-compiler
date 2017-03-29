
#include "../framework/integration_driver.h"

typedef struct {
	int a, b;
} pair;

int main() {
	int n, i;
	pair* arr;

	printf("Input the number of structures to allocate on the stack: ");
	scanf("%d", &n);

	printf("allocating %d bytes on heap\n", n * sizeof(pair));

	arr = malloc(n * sizeof(pair));

	printf("arr points to %p\n", arr);

	for(i = 0; i < n; ++i) {
		(*((pair*)arr + i)).a = random_get();
		printf("i = %d:  %d, %d\n", i, (*((pair*)arr + i)).a, (*((pair*)arr + i)).b);
	}

	return 0;
}
