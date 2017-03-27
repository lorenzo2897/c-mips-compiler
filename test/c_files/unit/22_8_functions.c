/*d void function */
/*@ 4 7 0 4 */
/*@ 5 1 0 5 */
/*@ 57 32 0 57 */

int glob;

void set(int x) {
    glob = x;
}

int func(int a, int b, int c) {
    glob = 0;
    set(a);
    return glob;
}

