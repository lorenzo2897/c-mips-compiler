/*d unary assignment */
/*@ 0 1 0 1 */
/*@ 42 1 0 43 */
/*@ 4 2 0 6 */

int func(int a, int b, int c) {
    b += a;
    return b;
}

