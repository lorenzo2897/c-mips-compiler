/*d assign variables */
/*@ 5 23 0 6 */
/*@ 9 -767 0 6 */
/*@ -535 1 0 6 */

int func(int a, int b, int c) {
    int *pa = &a;
    int *ptcopy;
    char x;
    char* xp = &x;
    *xp = x;
    ptcopy = pa;
    *ptcopy = 6;
    return a;
}

