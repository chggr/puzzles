#include <stdio.h>

// Task description: Given an integer number, write a method to identify the
// longest sequence of 1s that could be created by fliping exactly one bit from
// 0 to 1.
//
// E.g. For integer 0b0111001101111 the method should return 7.
//
// Solution: The first implementation below uses a brute force algorithm to find
// the longest sequence of 1s after flipping exactly one bit from 0 to 1. It
// iterates through all bits of the given number and if the bit is zero, it
// sets the bit to 1 and calculates the length of the sequence of 1s in this
// new number. Finally it returns the longest sequence of 1s observed during
// the iterations. The runtime complexity of this algorithm is O(N^2).
//
// The second implementation achieves the same result with only O(N) runtime
// complexity. It iterates through the bits of the given integer, keeping track
// of the length of the current and previous sequence of 1s. When a double zero
// is encountered, the previous sequence length is set to 0 since we can only
// flip one bit from 0 to 1.

int get_bit(int number, int position) {
    return (number & (1 << position)) != 0;
}

int set_bit(int number, int position) {
    return number | (1 << position);
}

int longest_seq(int number) {
    int max_len = 0;
    int current_len = 0;
    for (int i = 0; i < 32; i++) {
        if (get_bit(number, i)) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        }
    }
    return max_len;
}

int find_seq(int number) {
    if (number == ~0) return 32;

    int max_len = 0;
    for (int i = 0; i < 32; i++) {
        if (get_bit(number, i)) continue;
        int len = longest_seq(set_bit(number, i));
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

int find_seq2(int number) {
    if (number == ~0) return 32;

    int max_len = 1;
    int current_len = 0;
    int previous_len = 0;

    while(number > 0) {
        if (number & 1) {
            current_len++;
        } else {
            previous_len = number & 2 ? current_len : 0;
            current_len = 0;
        }
        int seq_len = current_len + previous_len + 1;
        max_len = max_len > seq_len ? max_len : seq_len;
        number >>= 1;
    }
    return max_len;
}

int test_all_bits_zero() {
    return 1 == find_seq(0) && 1 == find_seq2(0);
}

int test_all_bits_one() {
    return 32 == find_seq(~0) && 32 == find_seq2(~0);
}

int test_max_sequence() {
    int number = 0b0111001101111;
    return 7 == find_seq(number) && 7 == find_seq2(number);
}

int main() {
    int counter = 0;
    if (!test_all_bits_zero()) {
        printf("All bits zero test failed.\n");
        counter++;
    }
    if (!test_all_bits_one()) {
        printf("All bits one test failed.\n");
        counter++;
    }
    if (!test_max_sequence()) {
        printf("Max sequence test failed.\n");
        counter++;
    }
    printf("%d tests failed.\n", counter); ;
}

