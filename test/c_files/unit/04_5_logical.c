/*d boolean operators */
/*@ 0 0 0 0 */
/*@ 0 0 1 0 */
/*@ 0 1 0 0 */
/*@ 0 1 1 1 */
/*@ 1 0 0 1 */
/*@ 1 0 1 1 */
/*@ 1 1 0 1 */
/*@ 1 1 1 1 */

int func(int a, int b, int c) {
    return a || b && c;
}

