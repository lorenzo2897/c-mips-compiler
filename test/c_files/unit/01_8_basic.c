/*d assigning global variables */
/*@ 5 6 0 5 */
/*@ 0 6 0 0 */
/*@ 222 6 0 222 */
/*@ -78 63 0 -78 */

int andmore = 2;

int func(int a, int b, int c) {
    andmore = a;
    b = andmore;
	return b;
}

