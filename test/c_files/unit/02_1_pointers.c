/*d assign variables */
/*@ 5 555 0 555 */
/*@ 9 0 0 0 */
/*@ -535 4 0 4 */

int func(int a, int b, int c) {
    int *pa = &a;
    int *pb = &b;
    *pa = *pb;
    return a;
}

