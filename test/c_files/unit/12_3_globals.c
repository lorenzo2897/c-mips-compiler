/*d global struct addressing */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

struct g {
    int a, b;
} globvar;

int func(int a, int b, int c) {
    struct g *p = &globvar;
    p->b = a;
    return (*p).b;
}

