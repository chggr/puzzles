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
//
// The second implementation below is a variation of binary search and can be
// used when both arrays have the same length. Using this algorithm we can find
// the median in just O(logn), where n is the length of the arrays. It first
// calculates the median of each array and according to which one is greater,
// calls itself recursively using the first half or the second half of each
// array.

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

double max(int a, int b) {
    return a > b ? a : b;
}

double min (int a, int b) {
    return a > b ? b : a;
}

double median_of(int array[], int size) {
    return size % 2 == 1 ? array[size / 2] :
        (array[size / 2] + array[size / 2 + 1]) / 2.0;
}

double median_opt(int a[], int b[], int size) {

    if (a == NULL && b == NULL) return 0.0;
    if (a == NULL) return median_of(b, size);
    if (b == NULL) return median_of(a, size);

    // Base cases
    if (size == 1) return (a[0] + b[0]) / 2.0;
    if (size == 2) return (max(a[0], b[0]) + min(a[1], b[1])) / 2.0;

    double a_med = median_of(a, size);
    double b_med = median_of(b, size);

    if (a_med == b_med) return a_med;
    if (a_med > b_med) {
        return size % 2 == 0 ?
            median_opt(a, b + size / 2 - 1, size - size / 2 + 1) :
            median_opt(a, b + size / 2, size - size / 2);
    } else {
        return size % 2 == 0 ?
            median_opt(a + size / 2 - 1, b, size - size / 2 + 1) :
            median_opt(a + size / 2, b, size - size / 2);
    }
}

int test_one_empty() {
    int a[] = {1, 2, 3};
    return 2.0 == median(a, 3, NULL, 0) &&
           2.0 == median(NULL, 0, a, 3) &&
           2.0 == median_opt(a, NULL, 3) &&
           2.0 == median_opt(NULL, a, 3);
}

int test_both_empty() {
    return 0.0 == median(NULL, 0, NULL, 0) &&
           0.0 == median_opt(NULL, NULL, 0);
}

int test_unique() {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    return 3.5 == median(a, 3, b, 3) &&
           3.5 == median(b, 3, a, 3) &&
           3.5 == median_opt(a, b, 3) &&
           3.5 == median_opt(b, a, 3);
}

int test_repeating() {
    int a[] = {1, 1, 1};
    int b[] = {1, 1, 1};
    return 1.0 == median(a, 3, b, 3) &&
           1.0 == median(b, 3, a, 3) &&
           1.0 == median_opt(a, b, 3) &&
           1.0 == median_opt(b, a, 3);
}

int test_negative() {
    int a[] = {-3, -2, -1, 0};
    int b[] = {1, 2, 3, 4};
    return 0.5 == median(a, 4, b, 4) &&
           0.5 == median(b, 4, a, 4) &&
           0.5 == median_opt(a, b, 4) &&
           0.5 == median_opt(b, a, 4);
}

int test_large_same_length() {
    int a[] = {-10, -4, -1, 3, 7, 9, 14};
    int b[] = {-7, -3, 0, 1, 5, 15, 22};
    return 2.0 == median(a, 7, b, 7) &&
           2.0 == median(b, 7, a, 7) &&
           2.0 == median_opt(a, b, 7) &&
           2.0 == median_opt(b, a, 7);
}

int test_large_diff_length() {
    int a[] = {-10, -4, -1, 3, 7, 9, 14, 17, 19, 21};
    int b[] = {-7, -3, 0, 1, 5, 15, 22};
    return 5.0 == median(a, 10, b, 7) &&
           5.0 == median(b, 7, a, 10);
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
    if (!test_large_same_length()) {
        printf("Large same length array test failed!\n");
        counter++;
    }
    if (!test_large_diff_length()) {
        printf("Large different length array test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

