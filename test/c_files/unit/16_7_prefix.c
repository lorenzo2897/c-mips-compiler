/*d postfix */
/*@ 0 1 0 2 */
/*@ 42 1 0 86 */
/*@ 4 2 0 10 */

int func(int a, int b, int c) {
    c = ++a;
    return a + c;
}

