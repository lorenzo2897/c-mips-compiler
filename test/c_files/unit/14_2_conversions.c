/*d type conversion: char to unsigned short */
/*@ 0 0 0 0 */
/*@ 255 0 0 65535 */
/*@ -1 0 0 65535 */
/*@ 256 0 0 0 */
/*@ 258 0 0 2 */

int func(int a, int b, int c) {
    char c1 = a;
    unsigned short c2 = c1;
    return c2;
}

