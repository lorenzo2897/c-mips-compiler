/*d double negative sign */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 156736 0 0 156736 */
/*@ -156736 0 0 -156736 */

int func(int a, int b, int c) {
    int neg = -a;
    return -neg;
}

