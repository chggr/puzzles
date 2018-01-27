#include <stdio.h>

// Task description: Given an integer, write a method to return the number of
// bits in its binary representation that are equal to 1.
//
// E.g. For integer 7, the method should return 3.
//      For integer 0, the method should return 0.
//      For integer -1 the method should return 32.
//
// Solution: The first implementation below uses a while loop to test whether
// each bit in the input integer is equal to one. It initially creates a mask
// and sets the first bit to one. In every iteration it moves the bit by one
// position to the left, using the AND operation to test whether that bit is
// set in the input number. The runtime complexity of this approach is O(n),
// where n is the total number of bits.
//
// The second implementation uses clever bitwise operations to solve the
// problem in O(m), where m is the number of bits in the input number that are
// set to one. It works by continuously subtracting one from the input number
// and ANDing the result with that number. This basically has the effect of
// removing the rightmost bit in the number's binary representation that is set
// to one. This operation is repeated until all one bits have been counted.

//            n            n-1          n&(n-1)
//         0000001       0000000        0000000
//         0000010       0000001        0000000
//         0000011       0000010        0000010
//         0011000       0010111        0010000
//
// Negative numbers are represented in two's complement which can be derived
// from the binary representation of the positive number by negating all bits
// and then adding one. Therefore when a 32-bit signed integer takes value -1,
// all its 32 bits are set to 1.

int bit_count(int num) {
    int result = 0;
    int mask = 1;
    while (mask != 0) {
        result += (mask & num) != 0 ? 1 : 0;
        mask <<= 1;
    }
    return result;
}

int bit_count2(int num) {
    int result = 0;
    while (num != 0) {
        num = num & (num - 1);
        result++;
    }
    return result;
}

int test_bit_count() {
    return 0 == bit_count(0) &&
           1 == bit_count(1) &&
           1 == bit_count(2) &&
           2 == bit_count(3) &&
           3 == bit_count(7) &&
           32 == bit_count(-1) &&
           31 == bit_count(-2);
}

int test_bit_count2() {
    return 0 == bit_count2(0) &&
           1 == bit_count2(1) &&
           1 == bit_count2(2) &&
           2 == bit_count2(3) &&
           3 == bit_count2(7) &&
           32 == bit_count2(-1) &&
           31 == bit_count2(-2);
}

int main() {
    int counter = 0;
    if (!test_bit_count()) {
        printf("Bit count test failed!\n");
        counter++;
    }
    if (!test_bit_count2()) {
        printf("Bit count 2 test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

