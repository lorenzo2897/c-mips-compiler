/*d assign variables */
/*@ 5 9 0 9 */
/*@ 9 41 0 41 */
/*@ -535 -6666 0 -6666 */

int func(int a, int b, int c) {
    int *pa = &a;
    *pa = b;
    return a;
}

