/*d array unary ops */
/*@ 3 0 0 3 */
/*@ 5 23 0 28 */
/*@ 6 -10 0 -4 */
/*@ 0 0 0 0 */

int func(int a, int b, int c) {
    int arr[12];
    arr[7] = a;
    arr[7] += b;
    return arr[7];
}

