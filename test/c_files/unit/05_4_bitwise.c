/*d bitwise operators: not */
/*@ 0 0 0 -1 */
/*@ 0 3673 0 -3674 */
/*@ 76 255 0 -256 */
/*@ 21845 43690 0 -43691 */
/*@ 21845 112 0 -113 */

int func(int a, int b, int c) {
    return ~b;
}

