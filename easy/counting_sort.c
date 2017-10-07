#include <stdio.h>

// Task description: Given an array of integers that records people's ages
// [0, 100], implement a sorting algorithm to sort the array in O(n).
//
// Solution: The implementation below uses counting sort, a sorting algorithm
// that can be used if the elements to be sorted are between a specific range.
// It loops through the input array only once, counting the number of elements
// having each key value. The runtime complexity is O(n) and space complexity
// is O(k), where k is the range of key values.

void sort(int input[], int size) {
    int temp[101] = {0};
    for (int i = 0; i < size; i++) {
        temp[input[i]]++;
    }

    int current = 0;
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j < temp[i]; j++) {
            input[current++] = i;
        }
    }
}

int is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return 0;
    }
    return 1;
}

int main() {
    int ages[] = {12, 34, 65, 4, 78, 9, 43, 98, 51, 12};
    sort(ages, 10);
    if (!is_sorted(ages, 10)) {
        printf("Input array has not been sorted!\n");
    } else {
        printf("Input array is sorted.\n");
    }
}

