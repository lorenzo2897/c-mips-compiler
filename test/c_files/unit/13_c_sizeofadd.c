/*d sizeof addition */
/*@ 0 0 0 4 */

int func(int a, int b, int c) {
    return sizeof(a + b);
}

