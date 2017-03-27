/*d no arguments */
/*@ 0 0 0 23 */
/*@ 5 0 0 23 */

int sub() {
    return 23;
}

int func(int a, int b, int c) {
    return sub();
}

