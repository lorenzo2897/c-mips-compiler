/*d for loop: nested */
/*@ 0 0 0 0 */
/*@ 0 1 0 0 */
/*@ 1 1 0 1 */
/*@ 4 5 0 20 */
/*@ 7 12 0 84 */
/*@ 7 12 8 92 */

int func(int a, int b, int c) {
    int i, j;
    for(i = 0; i < a; i++) {
        for(j = 0; j < b; j++) {
            c++;
        }
    }
    return c;
}

