#include <stdio.h>

// Task description: Implement a method that adds two given positive integers
// without using the add operator (+) or any other arithmetic operator.
//
// Solution: In both implementations below we use bit operations to add the two
// numbers provided. The first implementation goes through all bits from 0 to 31
// and extracts the bit values from the input numbers. It then sets the bit in
// the result accordingly, by also taking into account any carry. The second
// implementation follows the same approach but is instead using XOR to get the
// result of summing the individual bits and a shifted AND to get the carry. It
// then iteratively calculates the sum and the carry until the carry reaches
// zero.

int add(int a, int b) {
    int carry = 0;
    int mask = 0;
    int a_bit = 0;
    int b_bit = 0;

    int result = 0;
    for (int i = 0; i < 32; i++) {
        mask = 1 << i;
        a_bit = a & mask;
        b_bit = b & mask;

        if (carry) {
            if (a_bit && b_bit) {
                result |= mask;
            } else if (!a_bit && !b_bit) {
                result |= mask;
                carry = 0;
            }
        } else {
            if (a_bit && b_bit) {
                carry = 1;
            } else if ((a_bit && !b_bit) || (!a_bit && b_bit)) {
                result |= mask;
            }
        }
    }
    return result;
}

int add_smart(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum;
        b = carry;
    }
    return a;
}

int test_add_zero() {
    return 0 == add(0, 0) &&
           0 == add_smart(0, 0) &&
           10 == add(10, 0) &&
           10 == add_smart(10, 0) &&
           10 == add(0, 10) &&
           10 == add_smart(0, 10);
}

int test_add() {
    return 10 == add(7, 3) &&
           10 == add_smart(7, 3) &&
           20 == add(10, 10) &&
           20 == add_smart(10, 10) &&
           1000 == add(123, 877) &&
           1000 == add_smart(123, 877);
}

int main() {
    int counter = 0;
    if (!test_add_zero()) {
        printf("Add zero test failed!\n");
        counter++;
    }
    if (!test_add()) {
        printf("Add test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

