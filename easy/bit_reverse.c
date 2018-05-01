#include <stdio.h>

// Task description: Given an integer, write a method to reverse all its bits
// and return the result.
//
// E.g. For integer 0xFFFF0000 the method should return 0x0000FFFF

int reverse(int num) {
    int res = 0;
    int bit_count = sizeof(unsigned int) * 8;
    for (int i = 0; i < bit_count; i++) {
        if ((num & (1 << i)) != 0) {
            res |= 1 << (bit_count - i - 1);
        }
    }
    return res;
}

int test_reverse() {
    return 0xFFFF0000 == reverse(0x0000FFFF) &&
           0x0000FFFF == reverse(0xFFFF0000) &&
           0xFF0000FF == reverse(0xFF0000FF);
}

int main() {
    int counter = 0;
    if (!test_reverse()) {
        counter++;
        printf("Reverse test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

