#include <stdio.h>

// Task description: Given an array of integers, implement the selection sort
// algorithm to sort the contents of the array in place in ascending order.
//
// E.g. Input array {1, -1, 0} should be sorted as {-1, 0, 1}.
//
// Solution: The selection sort algorithm is perhaps the easiest in-place
// sorting algorithm. It has overall complexity of n * n/2 = O(n^2), which
// includes n * n/2 comparisons and n swaps. This makes it very inefficient
// for larger input arrays. Nevertheless, The primary advantages are its
// simplicity and doing the sorting in-place, thus not requiring significant
// amount of auxiliary memory.

void sort(int input[], int size) {
    int min;
    int temp;

    if (!input || size < 2) return;

    for (int i = 0; i < size; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (input[j] < input[min]) min = j; 
        }
        if (min != i) {
            temp = input[i];
            input[i] = input[min];
            input[min] = temp;
        }
    }
}

int is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return 0;
    }
    return 1;
}

void main() {
    int input[] = {0, -1, -2, -1, 10, 3, 8};
    sort(input, 7);
    if (!is_sorted(input, 7)) {
        printf("Input array has not been sorted!\n");
    } else {
        printf("Input array is sorted.\n");
    }
}

