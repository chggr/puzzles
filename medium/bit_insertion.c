#include <stdio.h>

// Task description: Given two 32-bit integers (n and m) and two bit positions
// (i and j), write a method to insert m into n so that it starts at bit j and
// ends at bit i. You can assume that the bits j through i have enough space to
// fit all of m.
//
// E.g. For n = 0b10000000, m = 0b00000101, i = 4 and j = 2
//      the method should return 0b10010100
//
// Solution: The first step is to clear bits j through i in n, then shift m by
// i and finally merge them together. The most challenging part is to create
// the mask required to clear bits j through i in n. All bits in this mask
// should be ones except from the bits that need to be cleared, so that a
// logical AND between the mask and number n will give us the desired result.
// The two implementations below use different approaches to create the mask.

int insert(int n, int m, int start, int end) {
    int mask_length = start - end + 1;
    int mask = (1 << (max_length + 1)) - 1;
    mask <<= end;
    return (n & ~mask) | (m << end);
}

int insert2(int n, int m, int start, int end) {
    int left_submask = ~0 << (start + 1);
    int right_submask = ((1 << end) - 1);
    int mask = left_submask | right_submask;
    return (n & mask) | (m << end);
}

int test_non_overlap() {
    int n = 0b10000000;
    int m = 0b00000101;

    return 0b10010100 == insert(n, m, 4, 2) &&
           0b10010100 == insert2(n, m, 4, 2);
}

int test_overlap() {
    int n = 0b10010000;
    int m = 0b00000101;

    return 0b10010100 == insert(n, m, 4, 2) &&
           0b10010100 == insert2(n, m, 4, 2);
}

int main() {
    int counter = 0;
    if (!test_non_overlap()) {
        printf("Non overlap test failed!\n");
        counter++;
    }
    if (!test_overlap()) {
        printf("Overlap test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

