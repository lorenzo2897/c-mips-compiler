/*d type conversion: negative char and unsigned int */
/*@ 0 0 0 0 */
/*@ -1 0 0 -1 */

int func(int a, int b, int c) {
    char cneg = a;
    unsigned int ui = cneg;
    return ui;
}

