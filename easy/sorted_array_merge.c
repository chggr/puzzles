#include <stdio.h>

// Task description: Given two sorted arrays A and B, write a method that
// will merge B into A. A has enough capacity at the end to hold B.
//
// E.g. For arrays A: {1, 3, 5, 7, 9, 0, 0, 0, 0} and  B: {2, 4, 6, 8}
//      the result after merge is: A: {1, 2, 3, 4, 5, 6, 7, 8, 9}
//
// Solution: The implementation below reads both arrays backwards and populates
// array A from the end towards the beginning. Note that we do not need to copy
// the remaining elements of A after we have run out of elements from B, since
// these elements will already be in place.

void merge(int a[], int size_a, int b[], int size_b) {
    int index_a = size_a - 1;
    int index_b = size_b - 1;
    int current = size_a + size_b - 1;

    while(index_a >= 0 && index_b >= 0) {
        a[current--] = a[index_a] >= b[index_b] ?
            a[index_a--] : b[index_b--];
    }

    while (index_b >= 0) {
        a[current--] = b[index_b--];
    }
}

int is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return 0;
    }
    return 1;
}

int test_A_empty() {
    int a[] = {0, 0, 0, 0};
    int b[] = {2, 4, 6, 8};
    merge(a, 0, b, 4);
    return is_sorted(a, 4);
}

int test_B_empty() {
    int a[] = {1, 3, 5, 7, 9};
    merge(a, 5, 0, 0);
    return is_sorted(a, 5);
}

int test_merge() {
    int a[] = {1, 3, 5, 7, 9, 0, 0, 0, 0};
    int b[] = {2, 4, 6, 8};
    merge(a, 5, b, 4);
    return is_sorted(a, 9);
}

int main() {
    int counter = 0;
    if (!test_A_empty()) {
        printf("A array empty test failed!\n");
        counter++;
    }
    if (!test_B_empty()) {
        printf("B array empty test failed!\n");
        counter++;
    }
    if (!test_merge()) {
        printf("Merge test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

