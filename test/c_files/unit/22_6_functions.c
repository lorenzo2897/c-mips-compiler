/*d recursive */
/*@ 4 7 0 11 */
/*@ 5 1 0 6 */
/*@ 57 32 0 89 */

int add(unsigned x, unsigned y) {
    if(y > 0) {
        return add(x + 1, y - 1);
    }
    return x;
}

int func(int a, int b, int c) {
    return add(a, b);
}

