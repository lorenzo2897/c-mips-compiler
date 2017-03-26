/*d assign variables */
/*@ 5 0 0 222 */
/*@ 0 0 0 222 */

int func(int a, int b, int c) {
	int local = 8, another = 659, andmore = 222;
	local = another;
	another = andmore;
	local = andmore;
	return local;
}

