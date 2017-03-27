/*d float and double decrement */
/*@ 0 0 0 28 */
/*@ -5 0 0 28 */

int func(int a, int b, int c) {
    double f1;
    float f3;
    f1 = 5.0;
    f3 = 8.0f;
    f1--;
    f3--;
    return f1 * f3;
}

