/*d boolean operators: not */
/*@ 0 0 0 1 */
/*@ 0 0 1 1 */
/*@ 0 1 0 0 */
/*@ 0 1 1 0 */
/*@ 0 723 0 0 */
/*@ 0 -232 1 0 */

int func(int a, int b, int c) {
    return !b;
}

