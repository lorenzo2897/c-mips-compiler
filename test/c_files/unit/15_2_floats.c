/*d float and int */
/*@ 0 0 0 4 */
/*@ -5 0 0 -1 */
/*@ 9 0 0 13 */

int func(int a, int b, int c) {
    float f = 2.2f + 1.8f;
    f += a;
    return f;
}

