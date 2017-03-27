/*d float and double increment */
/*@ 0 0 0 54 */
/*@ -5 0 0 54 */

int func(int a, int b, int c) {
    double f1;
    float f3;
    f1 = 5.0;
    f3 = 8.0f;
    f1++;
    f3++;
    return f1 * f3;
}

