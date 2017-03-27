/*d array with ptr arithm. */
/*@ 3 0 0 3 */
/*@ 5 23 0 28 */
/*@ 6 -10 0 -4 */
/*@ 0 0 0 0 */

int func(int a, int b, int c) {
    int arr[12];
    int* alias;
    alias = arr;
    *(alias + 5) = a;
    arr[6] = b;
    *(arr + 7) = *(alias + 5) + alias[6];
    return arr[7];
}

