/*d sizeof struct */
/*@ 0 0 0 20 */

struct g {
    int a, b, c, d, e;
};

int func(int a, int b, int c) {
    struct g myg;
    return sizeof(myg);
}

