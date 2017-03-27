/*d basic switch */
/*@ 0 4 0 43 */
/*@ 1 7 0 4 */
/*@ 2 234 0 6 */
/*@ 3 234 0 234 */

int func(int a, int b, int c) {
    c = 43;
    switch(a) {
        case 1:
            c = 4;
            break;
        case 2:
            c = 6;
            break;
        case 3:
            c = b;
            break;
    }
    return c;
}

