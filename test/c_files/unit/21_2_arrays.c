/*d global array */
/*@ 3 0 0 3 */
/*@ 5 23 0 28 */
/*@ 6 -10 0 -4 */
/*@ 0 0 0 0 */

int arr[12];

int func(int a, int b, int c) {
    arr[5] = a;
    arr[6] = b;
    arr[7] = arr[5] + arr[6];
    return arr[7];
}

