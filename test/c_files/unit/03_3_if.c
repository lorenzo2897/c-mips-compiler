/*d variable if */
/*@ 5 23 0 443 */
/*@ 1 0 0 443 */
/*@ 9 0 0 443 */
/*@ -353 0 0 443 */
/*@ 0 0 0 4 */

int func(int a, int b, int c) {
    if(a) {
        return 443;
    }
    return 4;
}

