/*d sizeof char addition */
/*@ 0 0 0 4 */

int func(int a, int b, int c) {
    char c1, c2;
    return sizeof(c1 + c2);
}

