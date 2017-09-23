#include <stdio.h>

// Task description: Given two integers, write a method to determine the number
// of bits that need to be flipped to convert one integer to the other.

int bit_diff(int a, int b) {
    int xor = a ^ b;
    int count = 0;
    while (xor) {
        count += xor & 1;
        xor >>= 1;
    }
    return count;
}

int test_no_diff() {
    return 0 == bit_diff(0b01010, 0b01010);
}

int test_diff() {
    return 1 == bit_diff(0b1001, 0b1000) &&
           2 == bit_diff(0b1001, 0b0101) &&
           3 == bit_diff(0b1001, 0b0100) &&
           4 == bit_diff(0b1001, 0b0110);
}

int main() {
    int counter = 0;
    if (!test_no_diff()) {
        printf("No differences test failed!\n");
        counter++;
    }
    if (!test_diff()) {
        printf("Differences test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

