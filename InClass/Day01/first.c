#include <stdio.h>

/**
 * A1 O(n)
 * B1 O(1)
 * C1 O(log n)
 *
 * A2 O(n)
 * B2 O(m)
 * C2 O(1)
 *
 * A3 O(n)
 * B3 O(1)
 * C3 O(1)
 *
 * A4 O(n)
 * B4 O(m)
 * C4 O(n)
 */

void problem2();

int main() {
    problem2();
}

void problem2() {
    int a = 0, b = 1;
    int sum = 0;
    while(b < 4000000) {
        if((b & 1) == 0)
            sum += b;
        int temp = a;
        a = b;
        b = a + temp;
    }
    printf("%d\n", sum);
}

