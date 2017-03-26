/*d anonymous struct */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

int func(int a, int b, int c) {
    struct {
        char a;
        int b;
    } small;

    struct {
        int a, b, c, d;
    } local;

    small.b = a;
    local.d = small.b;
    return local.d;
}

