#include <stdio.h>

// Task description: Given a sorted array of integers that has been rotated an
// unknown number of times, write a method to return the index of an element in
// the array or -1 if not found. The array was originally sorted in ascending
// order.
//
// E.g. For array {6, 7, 8, 9, 10, 1, 2, 3, 4, 5} and element 3
//      the method should return 7.
//
// Solution: The implementation below is a modified version of binary search
// that reads the middle element and identifies which part of the array is
// normally ordered and which not. It then narrows down the search into the
// part of the array that likely contains the given element.
//
// Special handling is required in cases where the array contains many
// duplicate elements. In such cases we need to identify which half does not
// contain duplicates and search it. The runtime complexity of this algorithm
// is O(logn), but will degrade to O(n) if the array contains only duplicate
// elements.

int search(int input[], int low, int high, int val) {
    if (low > high) return -1;

    int mid = (low + high) / 2;
    if (input[mid] == val) return mid;

    if (input[low] < input[mid]) {
        // low to mid is normally ordered;
        if (val >= input[low] && val < input[mid]) {
            return search(input, low, mid - 1, val);
        } else {
            return search(input, mid + 1, high, val);
        }
    } else if (input[low] > input[mid]) {
        // mid to high is normally ordered.
        if (val > input[mid] && val <= input[high]) {
            return search(input, mid + 1, high, val);
        } else {
            return search(input, low, mid - 1, val);
        }
    } else {
        // Left or right half contains only duplicates.
        if (input[mid] != input[high]) {
            return search(input, mid + 1, high, val);
        } else {
            // We need to search both halves.
            int result = search(input, low, mid - 1, val);
            return result == -1 ? search(input, mid + 1, high, val) : result;
        }
    }
    return -1;
}

int test_found() {
    int input[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    return 1 == search(input, 0, 9, 7) &&
           7 == search(input, 0, 9, 3);
}

int test_not_found() {
    int input[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    return -1 == search(input, 0, 9, 11);
}

int test_duplicates() {
    int input[] = {6, 6, 6, 6, 6, 6, 6, 1, 2, 6};
    return 7 == search(input, 0, 9, 1) &&
           -1 == search(input, 0, 9, 5);
}

int main() {
    int counter = 0;
    if (!test_found()) {
        printf("Found test failed!\n");
        counter++;
    }
    if (!test_not_found()) {
        printf("Not found test failed!\n");
        counter++;
    }
    if (!test_duplicates()) {
        printf("Duplicates test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

