/*d struct addressing and pointers */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

struct small {
    char a;
    int b;
};

struct mystruct {
    int el1, el2;
    char el3;
    struct small el4;
};

int func(int a, int b, int c) {
    struct mystruct x, y, *px, *py;
    px = &x;
    py = &y;
    px->el4.b = a;
    *py = x;
    return y.el4.b;
}

