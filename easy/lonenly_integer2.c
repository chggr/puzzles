#include <stdio.h>

// Task description: Given an integer array where every number occurs three
// times except one which occurs only once, find the unique element. Can this be
// done in O(n) time complexity and O(1) space complexity?
//
// E.g. for input array {1, 5, 8, 3, 1, 1, 8, 5, 5, 8}
//      the method should return 3
//
// Solution: One approach would be to sort the given array and then go through
// the sorted array to identify the unique element. The runtime complexity of
// this approach is O(n * logn) and space complexity O(1), which clearly does
// not satisfy the requirements.
//
// Another approach would be to go through the input array and use a map to
// store the number of occurrences of each element. Then traverse the map to
// identify the unique element. The runtime complexity of this algorithm is
// O(n) but space complexity is also O(n), which also does not satisfy the
// requirements.
//
// The implementation below goes through the input array 32 times to count the
// number of times each bit is set (assuming 32-bit integers). If this number
// is multiple of three, then the bit of the lonely integer at that position
// will be zero, otherwise one. The runtime complexity of this algorithm is O(n)
// and space complexity O(1), which satisfies the requirements.

int find (int array[], int size) {
    int result = 0;
    int ones = 0;

    for (int i = 0; i < 32; i++) {
        ones = 0;
        for (int j = 0; j < size; j++) {
            if ((array[j] & (1 << i)) != 0) ones++;
        }
        if (ones % 3 != 0) result |= (1 << i);
    }
    return result;
}

int test_empty_array() {
    return 0 == find(NULL, 0);
}

int test_one_element() {
    int array[] = { 2 };
    return 2 == find(array, 1);
}

int test_many_elements() {
    int array[] = {1, 5, 8, 3, 1, 1, 8, 5, 5, 8};
    return 3 == find(array, 10);
}

int test_negative_elements() {
    int array[] = {-2, 5, 8, -5, -2, -2, 8, 5, 5, 8};
    return -5 == find(array, 10);
}

int main() {
    int counter = 0;
    if (!test_empty_array()) {
        counter++;
        printf("Empty array test failed!\n");
    }
    if (!test_one_element()) {
        counter++;
        printf("One element test failed!\n");
    }
    if (!test_many_elements()) {
        counter++;
        printf("Many elements test failed!\n");
    }
    if (!test_negative_elements()) {
        counter++;
        printf("Negative elements test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

