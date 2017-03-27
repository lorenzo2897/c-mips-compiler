/*d six arguments */
/*@ 0 0 0 0 */
/*@ 5 0 0 5 */
/*@ 23 0 0 23 */
/*@ -4 0 0 -4 */
/*@ -4 93 2 91 */
/*@ 4 8 7 19 */
/*@ -1 1 -10 -10 */

int add(int a, int b, int c, int d, int e, int f) {
    return d + e + f;
}

int func(int a, int b, int c) {
    return add(3, 5, 7, a, b, c);
}

