/*d float and double multiplication and division */
/*@ 0 0 0 8 */
/*@ -5 0 0 8 */

int func(int a, int b, int c) {
    double f1, f2;
    float f3, f4;
    f1 = 5.3;
    f2 = 0.7;
    f3 = 8.0f;
    f4 = 6.0f;
    return f3 * f4 / (f1 + f2);
}

