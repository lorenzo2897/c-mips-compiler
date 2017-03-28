
/* custom */

void print_str(char* a);
void print_int(int a);
void print_uint(int a);
void print_float(double a);
void print_ptr(void* a);

void scan_str(char* a);
void scan_int(int* a);
void scan_uint(int* a);

void random_seed();
int random_get();

double math_sqrt(double a);


/* standard library */

int printf(const char *format, ...);
int scanf(const char *format, ...);

void* malloc (unsigned size);
void free (void* ptr);
