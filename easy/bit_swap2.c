#include <stdio.h>

// Task description: Given an integer and two bit positions in its binary
// representation, write a method that swaps n bits at these positions. The two
// areas to be swapped will not overlap.
//
// E.g. for number 0b111001010101110, positions 11 / 3 and count 3
//      the answer is: 0b111111010100010
//
// Solution: The first implementation below uses masks to isolate the bits that
// need to be swapped. It then creates a swap mask by moving the bits to be
// be swapped in the correct position. Finally it clears the corresponding bits
// in the original number and applies the swap mask.
//
// The second implementation uses a loop to swap one bit at a time. It reads the
// two bits to be swapped and performs the swap by clearing the corresponding
// bits in the given number and applying the swapped bits.

int swap(int num, int from, int to, int count) {
    int mask = (1 << (count + 1)) - 1;

    int from_mask = mask << (from - count);
    int to_mask = mask << (to - count);

    // Create mask with swapped bits.
    int swapped = ((num & from_mask) >> (from - to)) |
                  ((num & to_mask) << (from - to));

    // Clean up swap positions and apply mask.
    num = num & (~from_mask);
    num = num & (~to_mask);
    return num | swapped;
}

int swap2(int num, int from, int to, int count) {
    while (count > 0) {
        int from_bit = num & (1 << from);
        int to_bit = num & (1 << to);

        num = (num & ~(1 << from)) | (to_bit << (from - to));
        num = (num & ~(1 << to)) | (from_bit >> (from - to));

        from--;
        to--;
        count--;
    }
    return num;
}

int test_swap() {
    int num = 0b111001010101110;
    int expected = 0b111111010100010;
    return expected == swap(num, 11, 3, 3) &&
           expected == swap2(num, 11, 3, 3);
}

int main() {
    int counter = 0;
    if (!test_swap()) {
        counter++;
        printf("Swap test failed.\n");
    }
    printf("%d tests failed.\n", counter);
}

