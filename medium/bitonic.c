#include <stdio.h>

// Task description: Given an array of N positive integers, write a method to
// return the length of the longest bitonic subsequence. A subsequence is called
// bitonic if it is first increasing and then decreasing. A sorted array is also
// considered bitonic with either the increasing or decreasing part empty.
//
// E.g. for input {1, 11, 2, 10, 4, 5, 2, 1}
//      the longest bitonic subsequence is {1, 2, 10, 4, 2, 1}
//      therefore the method should return 6
//
// Solution: The implementation below breaks the problem into two parts. It
// first calculates the longest increasing subsequence for all elements in the
// input array. It then calculates the longest decreasing subsequence for all
// elements in the array. Finally it combines the two results to identify the
// longest bitonic subsequence. The runtime complexity of this algorithm is
// O(N ^ 2) and the space complexity is O(N) for the two auxiliary arrays.

int bitonic(int array[], int size) {

    // Calculate the longest increasing subsequence.
    int inc[size];
    for (int i = 0; i < size; i++) {
        inc[i] = 1;
        for (int j = 0; j < i; j++) {
            if (array[j] < array[i] && inc[j] + 1 > inc[i]) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    // Calculate the longest decreasing subsequence.
    int dec[size];
    for (int i = size - 1; i >= 0; i--) {
        dec[i] = 1;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[i] && dec[j] + 1 > dec[i]) {
                dec[i] = dec[j] + 1;
            }
        }
    }

    // Find the length of the longest bitonic subsequence.
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (inc[i] + dec[i] - 1 > max) {
            max = inc[i] + dec[i] - 1;
        }
    }
    return max;
}

int test_flat_bitonic() {
    int input[] = {7, 7, 7, 7, 7, 7, 7, 7, 7};
    return 1 == bitonic(input, 9);
}

int test_inverse_bitonic() {
    int input[] = {5, 4, 3, 2, 1, 2, 3, 4, 5};
    return 5 == bitonic(input, 9);
}

int test_bitonic() {
    int input[] = {1, 11, 2, 10, 4, 5, 2, 1};
    return 6 == bitonic(input, 8);
}

int main() {
    int counter = 0;
    if (!test_flat_bitonic()) {
        counter++;
        printf("Flat bitonic test failed!\n");
    }
    if (!test_inverse_bitonic()) {
        counter++;
        printf("Inverse bitonic test failed!\n");
    }
    if (!test_bitonic()) {
        counter++;
        printf("Bitonic test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

