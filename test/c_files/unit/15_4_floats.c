/*d negative float and double */
/*@ 0 0 0 -3 */
/*@ -5 0 0 -3 */

int func(int a, int b, int c) {
    float f = -2.2;
    double ff = -f;
    return -(ff + 0.8);
}

