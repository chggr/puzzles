#include <stdio.h>

// Task description: Given an array of integers, write a method that will return
// the kth smallest element in O(n).
//
// E.g. for array {5, 3, 8, 7, 1, 4, 9, 2, 6} and k = 3
//      the method should return 3
//
// Solution: The solution below implements the quickselect algorithm, that
// follows a similar approach to quicksort: it chooses a pivot element and
// partitions the data into two based on that pivot. After partitioning, the
// pivot will be in its final position, therefore it can be used to identify
// the side which the element we are searching for will be in. Instead of
// recursing on both sides like quicksort, quickselect only operates on one
// side, reducing the runtime complexity from O(n logn) to just O(n) on average.
// At the beginning it goes through n elements, then n/2, then n/4 and so on.
// The sum n + n/2 + n/4 + n/8 + ... asymptotically converges to 2n, giving an
// overall runtime complexity of O(n).
//
// Quickselect is in-place and beyond selecting the kth element also partially
// sorts the data. Unfortunately it is sensitive to the pivot chosen. In order
// to achieve O(n) performance, the choice of pivot should consistently decrease
// the search set exponentially. If bad pivots are chosen, performance can
// degrade to O(n ^ 2) in the worst case. This might occur for example when
// searching for the maximum element of a sorted set and using the first element
// as a pivot.
//
// If the input array has duplicate elements and the task is to get the kth
// smallest distinct element, the partitioning algorithm below will need to be
// changed so that it creates three chunks: one less than the pivot, another
// equal to the pivot and a third one greater than the pivot.

void swap(int array[], int a, int b) {
    if (a == b) return;
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int partition(int array[], int low, int high) {
    int pivot = array[(low + high) / 2];

    while (low <= high) {
        while(array[low] < pivot) low++;
        while(array[high] > pivot) high--;

        if (low <= high) {
            swap(array, low, high);
            high--;
            low++;
        }
    }
    return low - 1;
}

int rank(int array[], int size, int k) {
    if (k >= size || k < 0) return 0;

    int low = 0;
    int high = size - 1;
    int curr = -1;

    while (curr != k) {
        curr = partition(array, low, high);
        if (curr < k) low = curr + 1;
        else if (curr > k) high = curr - 1;
    }
    return array[curr];
}

int test_invalid_k() {
    int array[] = {5, 3, 8, 7, 1, 4, 9, 2, 6};
    return 0 == rank(array, 9, 11) &&
           0 == rank(array, 9, -2);
}

int test_non_repeating() {
    int array[] = {5, 3, 8, 7, 1, 4, 9, 2, 6};
    return 1 == rank(array, 9, 0) &&
           2 == rank(array, 9, 1) &&
           3 == rank(array, 9, 2) &&
           4 == rank(array, 9, 3) &&
           5 == rank(array, 9, 4) &&
           6 == rank(array, 9, 5) &&
           7 == rank(array, 9, 6) &&
           8 == rank(array, 9, 7) &&
           9 == rank(array, 9, 8);
}

int test_repeating() {
    int array[] = {5, 5, 8, 7, 1, 4, 9, 9, 6};
    return 1 == rank(array, 9, 0) &&
           4 == rank(array, 9, 1) &&
           5 == rank(array, 9, 2) &&
           5 == rank(array, 9, 3) &&
           6 == rank(array, 9, 4) &&
           7 == rank(array, 9, 5) &&
           8 == rank(array, 9, 6) &&
           9 == rank(array, 9, 7) &&
           9 == rank(array, 9, 8);
}

int main() {
    int counter = 0;
    if (!test_invalid_k()) {
        printf("Invalid k test failed!\n");
        counter++;
    }
    if (!test_non_repeating()) {
        printf("Non-repeating test failed!\n");
        counter++;
    }
    if (!test_repeating()) {
        printf("Repeating test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

