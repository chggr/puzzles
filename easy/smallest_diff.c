#include <stdio.h>

// Task description: Given two arrays of integers, find the pair of values
// that produce the smallest non-negative difference. Return the difference.
// How can the performance of your algorithm be optimized?
//
// E.g. For input arrays: {23, 65, 2, 18, 5} and {55, 19, 13, 42}
//      The output should be: 19 - 18 = 1
//
// Solution: The first implementation below is the brute force approach, where
// all elements from the first array are compared with all elements of the
// second array to identify and return the smallest difference. This approach
// is simple, but its runtime complexity is O(N * M) since the algorithm needs
// to go through all elements of both arrays.
//
// Performance can be greatly improved by initially sorting both arrays.Sorting
// will take O(N logN) for each array, but searching for the elements with the
// smallest difference can now be done more efficiently at O(N + M). This is
// the approach followed in the second implementation below, where the elements
// of both sorted arrays are visited sequentially to identify the smallest
// difference.

int abs(int n) {
    return n < 0 ? -n : n;
}

int smallest_diff(int a[], int asize, int b[], int bsize) {
    if (asize == 0 || bsize == 0) return -1;

    int min = abs(a[0] - b[0]);
    int diff;
    for (int i = 0; i < asize; i++) {
        for (int j = 0; j < bsize; j++) {
            diff = abs(a[i] - b[j]);
            if (diff < min) min = diff;
        }
    }
    return min;
}

int smallest_diff_sorted(int a[], int asize, int b[], int bsize) {
    if (asize == 0 || bsize == 0) return -1;

    int a_idx = 0;
    int b_idx = 0;
    int min = abs(a[0] - b[0]);
    int diff;
    while (a_idx < asize && b_idx < bsize) {
        diff = abs(a[a_idx] - b[b_idx]);
        if (diff < min) min = diff;

        if (a[a_idx] > b[b_idx]) {
            b_idx++;
        } else {
            a_idx++;
        }
    }
    return min;
}

int test_unsorted() {
    int a[] = {23, 65, 2, 18, 5};
    int b[] = {55, 19, 13, 42};
    return 1 == smallest_diff(a, 5, b, 4);
}

int test_unsorted_empty_array() {
    int a[] = {23, 65, 2, 18, 5};
    return -1 == smallest_diff(a, 5, 0, 0);
}

int test_sorted() {
    int a[] = {1, 5, 19, 22, 35};
    int b[] = {4, 13, 28, 42};
    return 1 == smallest_diff_sorted(a, 5, b, 4);
}

int test_sorted_empty_array() {
    int a[] = {1, 5, 19, 22, 35};
    return -1 == smallest_diff_sorted(a, 5, 0, 0);
}

int main() {
    int counter = 0;
    if (!test_unsorted()) {
        printf("Unsorted test failed!\n");
        counter++;
    }
    if (!test_unsorted_empty_array()) {
        printf("Unsorted empty array test failed!\n");
        counter++;
    }
    if (!test_sorted()) {
        printf("Sorted test failed!\n");
        counter++;
    }
    if (!test_sorted_empty_array()) {
        printf("Sorted empty array test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

