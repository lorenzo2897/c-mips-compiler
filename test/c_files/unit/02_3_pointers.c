/*d assign variables */
/*@ 5 23 0 23 */
/*@ 9 -767 0 -767 */
/*@ -535 1 0 1 */

int func(int a, int b, int c) {
    int *pa = &a;
    int *pb = &b;
    int **ppa = &pa;
    int *deref;
    deref = *ppa;
    *deref = *pb;
    return a;
}

