#include <stdio.h>

// Task description: Given an array of integers, implement the insertion sort
// algorithm to sort the contents of the array in place in ascending order.
//
// E.g. Input array {1, -1, 0} should be sorted as {-1, 0, 1}.
//
// Solution: The insertion sort algorithm is a fairly simple algorithm that
// builds the sorted result one element at a time. It iterates through all
// elements of the input array, consuming one element each time and growing a
// sorted output list. At each iteration, it removes one element from the input
// data, finds and inserts it into the correct location in the sorted list.
// Both average and worst case complexities are O(n^2), since each element will
// need to be swapped on average n/2 until it reaches its final position in the
// sorted list. Therefore this algorithm does not scale well for larger inputs.
// In practice though it is more efficient that other simple sorting algorithms
// such as bubble sort or selection sort.

void sort(int input[], int size) {
    int temp;

    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0 && input[j] < input[j - 1]; j--) {
            temp = input[j];
            input[j] = input[j - 1];
            input[j - 1] = temp;
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

