/*d shift right signed */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ 1932 0 0 1932 */
/*@ 1 5 0 0 */
/*@ 1024 10 0 1 */
/*@ 3072 9 0 6 */
/*@ -1 30 0 -1 */

int func(int a, int b, int c) {
    return a >> b;
}

