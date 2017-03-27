/*d one argument */
/*@ 0 0 0 0 */
/*@ 5 0 0 5 */
/*@ 23 0 0 23 */
/*@ -4 0 0 -4 */

int sub(int a) {
    return a;
}

int func(int a, int b, int c) {
    return sub(a);
}

