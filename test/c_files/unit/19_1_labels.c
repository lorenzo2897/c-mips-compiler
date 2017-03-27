/*d labels and goto */
/*@ 0 4 0 0 */
/*@ 1 7 0 1 */
/*@ 2 234 0 2 */

int func(int a, int b, int c) {
    c = a;
    goto skipc;
    c = b;
skipc:
    return c;
}

