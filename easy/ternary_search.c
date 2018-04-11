#include <stdio.h>

// Task description: Given a sorted integer array, write a method to find an
// integer using ternary search and return its index in the array or -1 if it
// does not exist. Ternary search is similar to binary search, but the range is
// divided by three in each recursive call. Is ternary search more efficient
// than binary search?
//
// E.g. for input array {1, 2, 3, 4, 5}
//      if the target is 4, the method should return 3
//      if the target is 7, the method should return -1
//
// Solution: The implementation below uses ternary search to find the given
// integer in the array. In every recursive call, it splits the search space in
// three parts and focuses on only one of these parts, effectively discarding
// 2/3 of the search space each time. Although this might seem more efficient
// than binary search, it really is not. Binary search makes log2(N) recursive
// calls and each one of them requires two comparisons. On the contrary, ternary
// search makes log3(N) recursive calls, but each call requires four comparisons.
// O(2 * log2(N)) is less than O(4 * log3(N)) because:
// 4 * log3(N) = 4 * log2(N) / log3(2) = 4 * log2(N) / 0.631 = 6.34 * log2(N)

int search(int array[], int target, int from, int to) {
    if (from > to) return -1;

    int mid_left = from + (to - from) / 3;
    int mid_right = from + 2 * (to - from) / 3;
    if (array[mid_left] == target) return mid_left;
    if (array[mid_right] == target) return mid_right;

    if (target < array[mid_left]) {
        return search(array, target, from, mid_left - 1);
    } else if (target > array[mid_right]) {
        return search(array, target, mid_right + 1, to);
    } else {
        return search(array, target, mid_left + 1, mid_right - 1);
    }
}

int test_one_element() {
    int array[] = {1};
    return 0 == search(array, 1, 0, 0) &&
           -1 == search(array, 2, 0, 0) &&
           -1 == search(array, -1, 0, 0);
}

int test_two_elements() {
    int array[] = {1, 2};
    return 0 == search(array, 1, 0, 1) &&
           1 == search(array, 2, 0, 1) &&
           -1 == search(array, 3, 0, 1) &&
           -1 == search(array, -1, 0, 1);
}

int test_three_elements() {
    int array[] = {1, 2, 3};
    return 0 == search(array, 1, 0, 2) &&
           1 == search(array, 2, 0, 2) &&
           2 == search(array, 3, 0, 2) &&
           -1 == search(array, 4, 0, 2) &&
           -1 == search(array, -1, 0, 2);
}

int test_small_array() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    return 2 == search(array, 3, 0, 13) &&
           9 == search(array, 10, 0, 13) &&
           0 == search(array, 1, 0, 13) &&
           13 == search(array, 14, 0, 13) &&
           -1 == search(array, 15, 0, 13) &&
           -1 == search(array, 0, 0, 13);
}

int test_large_array() {
    int array[1000000];
    for (int i = 0; i < 1000000; i++) {
        array[i] = i;
    }

    for (int i = 0; i < 1000000; i++) {
        int result = search(array, i, 0, 1000000);
        if (result != i) return 0;
    }
    return -1 == search(array, 1000000, 0, 1000000) &&
           -1 == search(array, -1, 0, 1000000);
}

int main() {
    int counter = 0;
    if (!test_one_element()) {
        counter++;
        printf("One element array search test failed!\n");
    }
    if (!test_two_elements()) {
        counter++;
        printf("Two elements array search test failed!\n");
    }
    if (!test_three_elements()) {
        counter++;
        printf("Three elements array search test failed!\n");
    }
    if (!test_small_array()) {
        counter++;
        printf("Small array search test failed!\n");
    }
    if (!test_large_array()) {
        counter++;
        printf("Large array search test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

