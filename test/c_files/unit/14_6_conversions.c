/*d type conversion: double and float */
/*@ 0 0 0 0 */
/*@ -5 0 0 -5 */
/*@ -1 0 0 -1 */
/*@ 256 0 0 256 */
/*@ 3 0 0 3 */

int func(int a, int b, int c) {
    double f = a;
    double fff;
    float ff = f;
    fff = ff;
    return fff;
}

