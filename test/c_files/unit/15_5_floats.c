/*d float addition and subtraction */
/*@ 0 0 0 28 */
/*@ -5 0 0 28 */

int func(int a, int b, int c) {
    float f1, f2, f3;
    f1 = 4.3f;
    f2 = 0.7f;
    f3 = 33.0f;
    return f3 - (f2 + f1);
}

