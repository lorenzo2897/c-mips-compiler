/*d variable if else */
/*@ 1 23 0 443 */
/*@ 5 23 0 443 */
/*@ 9 0 0 443 */
/*@ -353 0 0 443 */
/*@ 0 0 0 65 */

int func(int a, int b, int c) {
    if(a) {
        return 443;
    } else {
        return 65;
    }
    return 4;
}

