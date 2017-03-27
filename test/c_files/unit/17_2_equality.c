/*d not equals: ints */
/*@ 0 1 0 1 */
/*@ 0 0 0 0 */
/*@ 4 2 0 1 */
/*@ -1 -1 0 0 */
/*@ 1 1 0 0 */
/*@ 1234 1234 0 0 */
/*@ -4 4 0 1 */

int func(int a, int b, int c) {
    return a != b;
}

