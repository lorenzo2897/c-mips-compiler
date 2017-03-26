/*d variable while loop with continue */
/*@ 345 0 0 2 */
/*@ -41 0 0 2 */

int func(int a, int b, int c) {
    c = 2;
    while(a) {
        a = b;
        continue;
        c = 465;
    }
    return c;
}

