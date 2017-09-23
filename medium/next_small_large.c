#include <stdio.h>

// Task description: Given a positive integer, write two methods to return the
// next largest number and the next smallest number that have the same number of
// 1 bits in their binary representation.
//
// E.g. For number 10 (0b1010) the answers are 9 (0b1001 and 12 (0b1100).
//      For number 22 (0b10110) the answers are 21 (0b10101) and 25 (0b11001).
//      for number 25 (0b11001) the answers are 22 (0b10110) and 26 (0b11010).
//
// Solution: In order to find the next largest number, we need to identify the
// first occurence of bit sequence "01" and count the number of trailing zeros
// and ones leading to this sequence. Once "01" is identified, we flip the
// leading zero to 1 and set all the bits after it to zero. The new number
// should have the same count of 1 bits as the old number, thus we still need
// to set trailing_count - 1 bits to 1. We do so starting from the least
// significant bit and moving towards the most significant bit, so that we can
// obtain the next largest number. A similar approach is used to get the next
// smallest number as well.

int get_bit(int number, int index) {
    return (number & (1 << index)) != 0;
}

int set_bit(int number, int index) {
    return number | (1 << index);
}

int unset_bit(int number, int index) {
    return number & ~(1 << index);
}

int set_bits_less(int number, int index) {
    return number | ((1 << index) - 1);
}

int unset_bits_less(int number, int index) {
    return number & ~((1 << index) - 1);
}

int next_largest(int number) {
    int trail_zeros = 0;
    int trail_ones = 0;
    int flip_pos = 0;

    while (!get_bit(number, flip_pos)) {
        flip_pos++;
        trail_zeros++;
        if (flip_pos > 32) return number;
    }

    while (get_bit(number, flip_pos)) {
        flip_pos++;
        trail_ones++;
        if (flip_pos > 32) return number;
    }

    number = set_bit(number, flip_pos);
    trail_ones--;
    number = unset_bits_less(number, flip_pos);
    number = set_bits_less(number, trail_ones);
    return number;
}

int next_smallest(int number) {
    int trail_zeros = 0;
    int trail_ones = 0;
    int flip_pos = 0;

    while(get_bit(number, flip_pos)) {
        flip_pos++;
        trail_ones++;
        if (flip_pos > 32) return number;
    }

    while(!get_bit(number, flip_pos)) {
        flip_pos++;
        trail_zeros++;
        if (flip_pos > 32) return number;
    }

    number = unset_bit(number, flip_pos);
    trail_ones++;
    trail_zeros--;
    number = unset_bits_less(number, flip_pos);
    return number | (((1 << trail_ones) - 1) << trail_zeros);
}

int test_next_smallest() {
    return 0b1001 == next_smallest(0b1010) &&
           0b10101 == next_smallest(0b10110) &&
           0b10110 == next_smallest(0b11001) &&
           0 == next_smallest(0) &&
           ~0 == next_smallest(~0);
}

int test_next_largest() {
    return 0b1100 == next_largest(0b1010) &&
           0b11001 == next_largest(0b10110) &&
           0b11010 == next_largest(0b11001) &&
           0 == next_largest(0) &&
           ~0 == next_largest(~0);
}

void main() {
    int counter = 0;
    if (!test_next_smallest()) {
        printf("Next smallest positive test failed!\n");
        counter++;
    }
    if (!test_next_largest()) {
        printf("Next largest positive test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

