/*d many arguments */
/*@ 0 0 0 0 */
/*@ 5 0 0 5 */
/*@ 23 0 0 23 */
/*@ -4 0 0 -4 */
/*@ -4 93 2 91 */
/*@ 4 8 7 19 */
/*@ -1 1 -10 -10 */

int add(int a, int b, int c, int d, int e, char f, double g, int h) {
    return b + f + g;
}

int func(int a, int b, int c) {
    return add(1, a, 3, 4, 5, b, c, 8);
}

