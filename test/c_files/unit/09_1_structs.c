/*d simple struct assignment and read */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

struct mystruct {
    int el1, el2, el3;
};

int func(int a, int b, int c) {
    struct mystruct x;
    x.el1 = c;
    x.el2 = b;
    x.el3 = a;
    return x.el3;
}

