/*d switch with default */
/*@ 0 4 0 5 */
/*@ 1 7 0 10 */
/*@ 2 234 0 49 */
/*@ 3 234 0 234 */

int func(int a, int b, int c) {
    c = 43;
    switch(a) {
        default:
            c = 5;
            break;
        case 1:
            c = 4;
        case 2:
            c += 6;
            break;
        case 3:
            c = b;
            break;
    }
    return c;
}

