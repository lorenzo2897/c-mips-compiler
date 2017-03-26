/*d nested struct assignment and read */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

struct small {
    int a, b;
};

struct mystruct {
    int el1, el2;
    struct small el3;
};

int func(int a, int b, int c) {
    struct mystruct x;
    x.el1 = c;
    x.el3.a = b;
    x.el3.b = a;
    return x.el3.b;
}

