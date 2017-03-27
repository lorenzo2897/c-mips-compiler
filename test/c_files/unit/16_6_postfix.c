/*d postfix */
/*@ 0 1 0 1 */
/*@ 42 1 0 85 */
/*@ 4 2 0 10 */

int func(int a, int b, int c) {
    c = a++;
    b--;
    return a + c + b;
}

