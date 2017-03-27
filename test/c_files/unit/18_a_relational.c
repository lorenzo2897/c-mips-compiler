/*d greater than or equal: float */
/*@ 0 0 0 1 */
/*@ 1 0 0 1 */
/*@ 2 0 0 0 */

int func(int a, int b, int c) {
    float f = 1.0f, g = a;
    return f >= g;
}

