#include <stdio.h>

// Task description: Given an array of positive integers, a peak is defined as
// a value that is greater than or equal to its adjacent elements and a valley
// is defined as a value that is less than or equal to its adjacent elements.
// Create an algorithm to sort the given array into a sequence of peaks and
// valleys.
//
// E.g. for array: {1, 3, 5, 4, 2}
//      the peak is 5 and the valleys are 1 and 2
//      an accepted solution is: {1, 5, 3, 4, 2}
//
// Solution: The easiest solution would be to sort the given array and then
// loop from the beginning to the middle of the array, swapping every element
// at an even index with the element at size - index. The runtime complexity of
// this solution is O(n logn), which is required for the initial sorting.
//
// The implementation below is more efficient and has a runtime complexity of
// O(n). It loops through the given array two elements at a time and for every
// position it identifies the maximum of that and its adjacent positions. It
// swaps swaps the maximum with the current element, thus creating a sequence
// of peak - valley - peak - valley, etc.

int get_max(int* array, int size, int x, int y, int z) {
    int val_x = x < 0 || x >= size ? -1 : array[x];
    int val_y = y < 0 || y >= size ? -1 : array[y];
    int val_z = z < 0 || z >= size ? -1 : array[z];

    if (val_x >= val_y && val_x >= val_z) return x;
    if (val_y >= val_x && val_y >= val_z) return y;
    return z;
}

void swap(int* array, int x, int y) {
    int tmp = array[x];
    array[x] = array[y];
    array[y] = tmp;
}

void sort(int* array, int size) {
    for (int i = 0; i < size; i += 2) {
        int max = get_max(array, size, i - 1, i, i + 1);
        if (i != max) swap(array, i, max);
    }
}

int equal(int* a, int* b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int test_already_sorted() {
    int array[] = {2, 1, 4, 3, 5};
    int expected[] = {2, 1, 4, 3, 5};
    sort(array, 5);
    return equal(expected, array, 5);
}

int test_sort_ascending() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {2, 1, 4, 3, 5};
    sort(array, 5);
    return equal(expected, array, 5);
}

int test_sort_descending() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {5, 3, 4, 1, 2};
    sort(array, 5);
    return equal(expected, array, 5);
}

int test_sort_rand() {
    int array[] = {9, 4, 3, 8, 5};
    int expected[] = {9, 4, 8, 3, 5};
    sort(array, 5);
    return equal(expected, array, 5);
}

int main() {
    int counter = 0;
    if (!test_already_sorted()) {
        printf("Already sorted test failed!\n");
        counter++;
    }
    if (!test_sort_ascending()) {
        printf("Sort ascending test failed!\n");
        counter++;
    }
    if (!test_sort_descending()) {
        printf("Sort descending test failed!\n");
        counter++;
    }
    if (!test_sort_rand()) {
        printf("Sort random test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

