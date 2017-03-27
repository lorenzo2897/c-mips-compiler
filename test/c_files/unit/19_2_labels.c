/*d labels and goto */
/*@ 0 4 0 4 */
/*@ 1 7 0 8 */
/*@ 2 234 0 236 */

int func(int a, int b, int c) {
    c = a;
    goto skipc;
middle:
    c += b;
    goto end;
    c = a;
skipc:
    goto middle;
end:
    return c;
}

