/*d less than or equal: ints */
/*@ 0 1 0 1 */
/*@ 0 0 0 1 */
/*@ 4 2 0 0 */
/*@ -1 -1 0 1 */
/*@ 1 1 0 1 */
/*@ 1234 1234 0 1 */
/*@ -4 4 0 1 */
/*@ 2 4 0 1 */

int func(int a, int b, int c) {
    return a <= b;
}

