#include <stdio.h>

// Task description: Given an array of integers, write two methods to find the
// minimum and maximum index so that if all elements were sorted between those
// two indices then the whole array would be sorted. Make sure that the smallest
// such subsequence is identified.
//
// E.g. for array: {4, 7, 10, 11, 7, 12, 6, 16, 18, 19}
//      the minimum index is 1 and maximum is 6
//
// Solution: The easiest implementation would be to sort a copy of the given
// array and simply compare the sorted with the original array to identify the
// indices of the first and last elements out of order. This approach has O(N)
// space complexity and O(N logN) runtime complexity, where N is the size of
// the array.
//
// The implementation below is more efficient. The index of the first element
// out of order is identified and the remaining of the array is searched for
// the minimum element out of order. The minimum index is then calculated and
// returned. A similar approach is also followed to identify the maximum index.
// Space complexity of this algorithm is O(1) and runtime complexity is O(N),
// where N is the size of the input array.

// Returns the index of the first element out of order.
int first_unordered(int n[], int size) {
    for (int i = 1; i < size; i++) {
        if (n[i] < n[i - 1]) return i;
    }
    return -1;
}

// Returns the index of the last element out of order.
int last_unordered(int n[], int size) {
    for (int i = size - 2; i >= 0; i--) {
        if (n[i] > n[i + 1]) return i;
    }
    return -1;
}

// Returns the start index of the unsorted sequence.
int start_index(int n[], int size) {
    int first = first_unordered(n, size);
    if (first == -1) return -1;

    int min = n[first];
    for (int i = first; i < size; i++) {
        if (n[i] < min) min = n[i];
    }

    for (int i = 0; i < size; i++) {
        if (n[i] >= min) return i;
    }
    return -1;
}

// Returns the end index of the unsorted sequence.
int end_index(int n[], int size) {
    int last = last_unordered(n, size);
    if (last == -1) return -1;

    int max = n[last];
    for (int i = last; i >= 0; i--) {
        if (n[i] > max) max = n[i];
    }

    for (int i = size - 1; i >= 0; i--) {
        if (n[i] <= max) return i;
    }
    return -1;
}

int test_ordered() {
    int n[] = {1, 3, 6, 7, 8, 10, 13, 21, 23, 28};
    return -1 == start_index(n, 10) &&
           -1 == end_index(n, 10);
}

int test_unordered() {
    int n[] = {4, 7, 10, 11, 7, 12, 6, 16, 18, 19};
    return 1 == start_index(n, 10) &&
           6 == end_index(n, 10);
}

int test_reverse_ordered() {
    int n[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    return 0 == start_index(n, 10) &&
           9 == end_index(n, 10);
}

int main() {
    int counter = 0;
    if (!test_ordered()) {
        printf("Ordered test failed!\n");
        counter++;
    }
    if (!test_unordered()) {
        printf("Unordered test failed!\n");
        counter++;
    }
    if (!test_reverse_ordered()) {
        printf("Reverse ordered test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

