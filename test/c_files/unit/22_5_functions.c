/*d two doubles */
/*@ 4 7 0 11 */
/*@ 5 1 0 6 */
/*@ -5 -21 0 -26 */

int add(double x, double y) {
    return x + y;
}

int func(int a, int b, int c) {
    return add(a, b);
}

