#include <stdio.h>

/*
 *     a        b        p
 *  +-----+  +-----+  +-----+
 *  | 100 |  | 100 |  |     |
 *  +-----+  +-----+  +-----+
 *     ^                 |
 *     |                 |
 *     +-----------------+
 *
 *     a        b        p
 *  +-----+  +-----+  +-----+
 *  | 200 |  | 100 |  |     |
 *  +-----+  +-----+  +-----+
 *              ^        |
 *              |        |
 *              +--------+
 *  *p == 100
 */

int question2();

int main() {
    question2();
    return 0;
}

int question2() {
    int i = 27;
    printf("i = %d\n", i);
    int* p = &i;
    *p = 35;
    printf("i = %d\n", i);
    int** pp = &p;
    **pp = -12;
    printf("i = %d\n", i);
}

/*
 * a) x        = 399
 *    &x       = 4f40
 *    y        = 4f42
 *    *y       = 23
 *    &y       = 4f44
 *    *p       = 399
 *    &r       = 4f4c
 *    **r      = 4f46
 *    ****r    = 4f46
 *    *(z + 2) = 4f48
 *    **z      = 4f46
 *
 * b) the 23 would change to 4f4c
 *
 * c) the value of z changes to 4f69
 *
 */
