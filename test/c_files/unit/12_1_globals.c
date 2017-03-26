/*d global variables read */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

int globvar;

int func(int a, int b, int c) {
    globvar = a;
    return globvar;
}

