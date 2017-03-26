/*d type conversion: char to unsigned char */
/*@ 0 0 0 0 */
/*@ 255 0 0 255 */
/*@ -1 0 0 255 */
/*@ 256 0 0 0 */
/*@ 258 0 0 2 */

int func(int a, int b, int c) {
    char c1 = a;
    unsigned char c2 = c1;
    return c2;
}

