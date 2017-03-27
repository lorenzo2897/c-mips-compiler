/*d struct parameter */
/*@ 4 7 0 11 */
/*@ 5 1 0 6 */
/*@ 57 32 0 89 */

struct s {
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n;
    char o, p, q;
};

struct s add(struct s x, struct s y) {
    struct s ret;
    ret.q = x.o + y.o;
    return ret;
}

int func(int a, int b, int c) {
    struct s x, y, res;
    x.o = a;
    y.o = b;
    res = add(x, y);
    return res.q;
}

