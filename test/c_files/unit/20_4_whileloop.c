/*d while loop: basic */
/*@ 3 0 0 3 */
/*@ 5 0 0 5 */
/*@ 6 0 0 5 */
/*@ 16 0 0 15 */

int func(int a, int b, int c) {
    int i = a;
    while(i) {
        i--;
        if(i == 5) continue;
        ++c;
    }
    return c;
}

