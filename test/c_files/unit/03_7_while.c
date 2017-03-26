/*d variable while loop */
/*@ 345 0 0 465 */
/*@ -41 0 0 465 */

int func(int a, int b, int c) {
    c = 2;
    while(a) {
        a = b;
        c = 465;
    }
    return c;
}

