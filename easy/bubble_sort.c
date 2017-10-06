#include <stdio.h>

// Task description: Given an array of integers, implement the bubble sort
// algorithm to sort the contents of the array in place in ascending order.
//
// E.g. Input array {1, -1, 0} should be sorted as {-1, 0, 1}.
//
// Solution: The bubble sort algorithm involves repeatedly iterating through
// the input array, comparing the elements in pairs and swapping them if they
// are not in order until the whole array is sorted. The average and worst-case
// complexity of this algorithm is O(n^2): each element will need to move n/2
// places on average to reach its final position (n in worst case). Best case
// complexity is O(n) when the input array is already sorted.

void sort(int input[], int size) {
    int sorted = 0;
    int temp;

    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < size - 1; i++) {
            if (input[i] > input[i + 1]) {
                sorted = 0;
                temp = input[i];
                input[i] = input[i + 1];
                input[i + 1] = temp;
            }
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

