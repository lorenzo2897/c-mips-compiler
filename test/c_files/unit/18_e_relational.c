/*d greater than or equal: double */
/*@ 0 0 0 1 */
/*@ 1 0 0 1 */
/*@ 2 0 0 0 */

int func(int a, int b, int c) {
    double f = 1.0, g = a;
    return f >= g;
}

