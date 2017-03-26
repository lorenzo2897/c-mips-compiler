/*d int** typedef */
/*@ 0 0 0 0 */
/*@ 1 0 0 1 */
/*@ -1 0 0 -1 */
/*@ 543 0 0 543 */
/*@ -1536 0 0 -1536 */

typedef int* intptr;

int func(int a, int b, int c) {
    intptr mypt, *myptpt;
    mypt = &a;
    myptpt = &mypt;
    return *(*myptpt);
}

