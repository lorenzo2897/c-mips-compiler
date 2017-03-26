/*d assign variable with constant */
/*@ 5 0 0 7 */
/*@ 0 0 0 7 */
/*@ 555 8 0 7 */
/*@ -5 0 8 7 */

int func(int a, int b, int c) {
	int local = 0;
	local = 7;
	return local;
}

