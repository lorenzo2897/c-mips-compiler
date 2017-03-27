/*d double addition and subtraction */
/*@ 0 0 0 28 */
/*@ -5 0 0 28 */

int func(int a, int b, int c) {
    double f1, f2, f3;
    f1 = 4.3;
    f2 = 0.7;
    f3 = 33.0;
    return f3 - (f2 + f1);
}

