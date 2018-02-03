#include <stdio.h>

// Task description: Given two sorted integer arrays, write a method to return
// the median of all values.
//
// E.g. for arrays {1, 2, 3} and {4, 5, 6} the method should return 3.5
//      for arrays {5, 6, 7} and {4, 6} the method should return 6.
//
// Solution: A brute force approach would be to allocate a new array of size
// equal to the sum of the given array sizes, add all elements to it, sort it
// and then calculate the median. If n is the total number of elements in both
// arrays, the space complexity of this approach would be O(n) and the runtime
// complexity will be O(n logn) if we use quicksort or mergesort.
//
// The implementation below is based on a much more efficient algorithm, with
// a space complexity of O(1) and runtime complexity of O(n). The algorithm uses
// the fact that both input arrays are already sorted. It picks up the smallest
// element from the head of each array, incrementing a counter and keeping track
// of the current and previous items that have been extracted. The iteration
// stops when the counter has reached (n + 1) / 2, where n is the total number
// of elements in both arrays. Finally the median is calculated using the
// current and previous values, depending on whether n is even or odd.

double median(int a[], int a_size, int b[], int b_size) {

    int a_idx = 0;
    int b_idx = 0;
    int current = 0;
    int previous = 0;
    int index = 0;

    while (1) {
        previous = current;
        if (a_idx < a_size && b_idx < b_size) {
            current = a[a_idx] < b[b_idx] ? a[a_idx++] : b[b_idx++];
            index++;
        } else if (a_idx < a_size) {
            current = a[a_idx++];
            index++;
        } else if (b_idx < b_size) {
            current = b[b_idx++];
            index++;
        } else {
            break;
        }

        if (index == (a_size + b_size) / 2 + 1) break;
    }
    return (a_size + b_size) % 2 == 0 ? (current + previous) / 2.0 : current;
}

int test_one_empty() {
    int a[] = {1, 2, 3};
    return 2.0 == median(a, 3, NULL, 0) &&
           2.0 == median(NULL, 0, a, 3);
}

int test_both_empty() {
    return 0.0 == median(NULL, 0, NULL, 0);
}

int test_unique() {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    return 3.5 == median(a, 3, b, 3) &&
           3.5 == median(b, 3, a, 3);
}

int test_repeating() {
    int a[] = {1, 1, 1};
    int b[] = {1, 1, 1};
    return 1.0 == median(a, 3, b, 3) &&
           1.0 == median(b, 3, a, 3);
}

int test_negative() {
    int a[] = {-3, -2, -1};
    int b[] = {1, 2};
    return -1.0 == median(a, 3, b, 2) &&
           -1.0 == median(b, 2, a, 3);
}

int main() {
    int counter = 0;
    if (!test_one_empty()) {
        printf("One array empty test failed!\n");
        counter++;
    }
    if (!test_both_empty()) {
        printf("Both arrays empty test failed!\n");
        counter++;
    }
    if (!test_unique()) {
        printf("Unique elements test failed!\n");
        counter++;
    }
    if (!test_repeating()) {
        printf("Repeating elements test failed!\n");
        counter++;
    }
    if (!test_negative()) {
        printf("Negative elements test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

