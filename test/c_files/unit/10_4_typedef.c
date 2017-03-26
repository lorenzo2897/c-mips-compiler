/*d struct typedef */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

struct small {
    char a;
    int b;
};

typedef struct small small_t;

int func(int a, int b, int c) {
    struct small s1;
    small_t s2;
    s1.b = a;
    s2 = s1;
    return s2.b;
}

