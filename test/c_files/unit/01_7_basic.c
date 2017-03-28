/*d assign local and global variables */
/*@ 5 0 0 222 */
/*@ 0 0 0 222 */

int andmore = 222;

int func(int a, int b, int c) {
    andmore = 222;
	return andmore;
}

