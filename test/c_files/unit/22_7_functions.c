/*d struct parameter */
/*@ 4 7 0 11 */
/*@ 5 1 0 6 */
/*@ 57 32 0 89 */

struct s {
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n;
    char o, p, q;
};

char add(struct s x, struct s y) {
    return x.o + y.o;
}

int func(int a, int b, int c) {
    struct s x, y;
    x.o = a;
    y.o = b;
    return add(x, y);
}

