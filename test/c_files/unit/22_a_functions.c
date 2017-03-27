/*d char and short parameters */
/*@ 4 7 0 11 */
/*@ 5 1 0 6 */
/*@ -5 -21 0 -26 */

int add(char x, short y) {
    return x + y;
}

int func(int a, int b, int c) {
    return add(a, b);
}

