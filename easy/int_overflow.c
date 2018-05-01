#include <stdio.h>

// Task description: Give two integer numbers, write a method to detect whether
// their sum will overflow.
//
// E.g. For input numbers 0x7FFFFFFF and 0x00000001 the sum will overflow.
//      For input numbers 0x0000FFFF and 0x000000FF the sum will not overflow.
//
// Solution: The sum of two integers can overflow only when the signs of the two
// numbers are the same. When overflow occurs, the sign of the sum flips to the
// opposite of the sign of the two integers. The implementation below uses this
// observation to detect overflow.
//
// An alternative solution would be to cast both numbers to long, add them and
// then check whether the result is greater than the maximum integer value.

int overflow(int a, int b) {
    return (a > 0 && b > 0 && a + b <= 0) ||
           (a < 0 && b < 0 && a + b >= 0);
}

int test_overflow() {
    return overflow(0x7FFFFFFF, 0x00000001) &&
           overflow(0x00000001, 0x7FFFFFFF) &&
           overflow(0x80000000, 0x80000000) &&
           overflow(0x8FFFFFFF, 0x8FFFFFFF);
}

int test_not_overflow() {
    return !overflow(0x00000001, 0x00000001) &&
           !overflow(0xFFFFFFFF, 0xFFFFFFFF);
}

int main() {
    int counter = 0;
    if (!test_overflow()) {
        counter++;
        printf("Overflow test failed!\n");
    }
    if (!test_not_overflow()) {
        counter++;
        printf("Not overflow test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

