/*d while loop: basic */
/*@ 0 0 0 0 */
/*@ 2 0 0 0 */
/*@ 3 0 0 1 */
/*@ 6 0 0 4 */

int func(int a, int b, int c) {
    int i = a;
    while(i > 2) {
        ++c;
        i--;
    }
    return c;
}

