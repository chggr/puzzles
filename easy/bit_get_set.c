#include <stdio.h>

// Task description: Given a 32-bit integer, implement three methods to get,
// set and unset a specific bit in that integer. Additionally implement a
// method to clear all bits from the Most Significant bit to a given index
// and a method to clear all bits from the Least Significant to a given index.

int get_bit(int number, int bit) {
    return (number & (1 << bit)) != 0;
}

int set_bit(int number, int bit) {
    return number | (1 << bit);
}

int unset_bit(int number, int bit) {
    return number & ~(1 << bit);
}

int clear_msb(int number, int i) {
    return number & ((1 << i) - 1);
}

int clear_lsb(int number, int i) {
    return number & ~((1 << i) - 1);
}

int test_get_bit() {
    return get_bit(0b10101, 0) && !get_bit(0b010101, 1);
}

int test_set_bit() {
    return 0b1000 == set_bit(0, 3);
}

int test_unset_bit() {
    return 0 == unset_bit(0b1000, 3);
}

int test_clear_msb() {
    return 0b000111 == clear_msb(0b111111, 3);
}

int test_clear_lsb() {
    return 0b111000 == clear_lsb(0b111111, 3);
}

int main() {
    int counter = 0;
    if (!test_get_bit()) {
        printf("Get bit test failed!\n");
        counter++;
    }
    if (!test_set_bit()) {
        printf("Get bit test failed!\n");
        counter++;
    }
    if (!test_unset_bit()) {
        printf("Get bit test failed!\n");
        counter++;
    }
    if (!test_clear_msb()) {
        printf("Clear MSB test failed!\n");
        counter++;
    }
    if (!test_clear_lsb()) {
        printf("Clear LSB test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

