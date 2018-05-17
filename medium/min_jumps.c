#include <stdio.h>

// Task description: Given an array of N integers, where each element represents
// the maximum number of steps that can be made forward from that element, write
// a method to return the minimum number of jumps required to reach the end of
// the array starting from the first element.
//
// E.g. for input array {1, 3, 5, 8, 9, 2, 6, 7, 6, 8}
//      the minimum number of steps is 3
//
//      for input array {2, 3, 0, 0, 0, 1, 3, 9, 3, 5}
//      the minimum number of steps is -1 (impossible)
//
// Solution: The implementation below uses a bottom-up dynamic programming
// approach to calculate the minimum number of jumps. It uses a memoization
// array to hold the minimum number of jumps required for each position of the
// input array. The memo array is populated from right to left and the final
// result is stored at its first position. The runtime complexity of this
// algorithm is O(N ^ 2) because at each position we might need to look up
// to N positions forward. The space complexity is O(N) for the memoization
// array.

int min_jumps(int array[], int size) {
    int memo[size];
    for (int i = size - 1; i >= 0; i--) {

        // Can we reach the end from here?
        if (i + array[i] >= size) {
            memo[i] = 1;
            continue;
        }

        memo[i] = -1;
        for (int j = 1; j <= array[i]; j++) {
            if (memo[i + j] == -1) continue;
            if (memo[i] == -1 || memo[i] > 1 + memo[i + j]) {
                memo[i] = 1 + memo[i + j];
            }
        }
    }
    return memo[0];
}

int test_jump_impossible() {
    int input[] = {2, 3, 0, 0, 0, 1, 3, 9, 3, 5};
    return -1 == min_jumps(input, 10);
}

int test_min_jumps_ones() {
    int input[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    return 10 == min_jumps(input, 10);
}

int test_min_jumps() {
    int input[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8};
    return 3 == min_jumps(input, 11);
}

int main() {
    int counter = 0;
    if (!test_jump_impossible()) {
        counter++;
        printf("Impossible jump test failed!\n");
    }
    if (!test_min_jumps_ones()) {
        counter++;
        printf("Min jumps ones test failed!\n");
    }
    if (!test_min_jumps()) {
        counter++;
        printf("Min jumps test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

