/*d explicit enum */
/*@ 0 0 0 7 */
/*@ 6 0 0 7 */

enum weekday {
    monday = 5,
    tuesday,
    wednesday,
    thursday = -2,
    friday,
    saturday,
    sunday
};

int func(int a, int b, int c) {
    enum weekday d;
    if(saturday) {
        d = tuesday;
    } else {
        d = wednesday;
    }
    return d;
}

