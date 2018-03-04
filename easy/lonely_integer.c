#include <stdio.h>

// Task description: Given an array of integers, where each integer except one
// occurs twice, find the unique integer. Can this be done in O(n) runtime and
// O(1) space complexity?
//
// E.g. For given array {6, 4, 9, 5, 6, 9, 4}
//      the output should be: 5
//
// Solution: A brute force approach would be to go through the array of integers
// once and store in a map the occurrence of each value. Then iterate through
// all map entries and return the item with count 1. Both the runtime and space
// complexity of this approach is O(n), which clearly does not satisfy the
// requirements of the problem.
//
// This problem can be solved in O(1) space by making the following observation:
// since all the elements in the array are duplicates except from one, the count
// of bits set to one at each position will be odd if the bit is set to one in
// the unique element or even if it is set to zero. Therefore we can simply
// compute the unique element by XORing all elements in the array.

int find(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= array[i];
    }
    return result;
}

int test_empty_array() {
    return 0 == find(NULL, 0);
}

int test_one_element() {
    int array[] = { 4 };
    return 4 == find(array, 1);
}

int test_many_elements() {
    int array[] = {6, 4, 9, 5, 6, 9, 4};
    return 5 == find(array, 7);
}

int test_negative_elements() {
    int array[] = {6, -4, -9, -5, 6, -9, -4};
    return -5 == find(array, 7);
}

int main() {
    int counter = 0;
    if (!test_empty_array()) {
        printf("Empty array test failed!\n");
        counter++;
    }
    if (!test_one_element()) {
        printf("One element test failed!\n");
        counter++;
    }
    if (!test_many_elements()) {
        printf("Many elements test failed!\n");
        counter++;
    }
    if (!test_negative_elements()) {
        printf("Negative elements test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

