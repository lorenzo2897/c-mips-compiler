/*d sizeof variable */
/*@ 0 0 0 4 */
/*@ 1 0 0 4 */
/*@ 2 0 0 4 */
/*@ 3 0 0 4 */
/*@ 4 0 0 4 */
/*@ 10 0 0 4 */

int func(int a, int b, int c) {
    return sizeof(a);
}

