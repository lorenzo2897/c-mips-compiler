/*d basic enum */
/*@ 0 0 0 1 */
/*@ 6 0 0 1 */

enum weekday {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

int func(int a, int b, int c) {
    enum weekday d;
    d = tuesday;
    return d;
}

