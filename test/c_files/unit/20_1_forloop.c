/*d for loop: factorial */
/*@ 0 0 0 0 */
/*@ 0 0 6 6 */
/*@ 65 0 0 0 */
/*@ 2 0 1 2 */
/*@ 3 0 1 6 */
/*@ 4 0 1 24 */
/*@ 5 0 1 120 */
/*@ 3 0 3 18 */

int func(int a, int b, int c) {
    int i;
    for(i = 1; i <= a; i++) {
        c *= i;
    }
    return c;
}

