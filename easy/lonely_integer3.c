#include <stdio.h>

// Task description: Given an integer array where every number occurs twice
// except from two numbers that are unique, write a method to find the unique
// elements.
//
// E.g. for input array {5, 2, 9, 5, 3, 1, 9, 2}
//      the method should return 3 and 1
//
// Solution: One approach would be to sort the array and then go through all
// elements to identify the unique ones. The runtime complexity in this case is
// O(n * logn) and the space complexity is O(1). Another approach would be to
// use a map to hold how many times each element has appeared in the array and
// then go through the map to pick up the unique elements. Both the runtime and
// space complexity of this approach is O(n).
//
// The implementation below first calculates the XOR of all elements. We know
// that the XOR of an element with itself is zero, so this will basically give
// us the XOR of the two unique elements. We then identify the first bit in this
// number that is set and we know that the two unique elements will differ in
// this bit position. Finally, we go through the input array once again,
// dividing the elements in two sets - one set will have this bit set and the
// other not. We obtain the two missing numbers by XORing the elements in each
// set. The runtime complexity of this approach is O(n) and the space complexity
// is O(1).

void find (int array[], int size, int* one, int* two) {

    int xor = 0;
    for (int i = 0; i < size; i++) {
        xor ^= array[i];
    }
    if (xor == 0) return;

    int bit = 0;
    while (xor % 2 == 0) {
        bit++;
        xor /= 2;
    }

    for (int i = 0; i < size; i++) {
        if ((array[i] & (1 << bit)) != 0) {
            *one ^= array[i];
        } else {
            *two ^= array[i];
        }
    }
}

int test_empty_array() {
    int one = 0;
    int two = 0;

    find(NULL, 0, &one, &two);
    return 0 == one && 0 == two;
}

int test_one_element() {
    int one = 0;
    int two = 0;
    int array[] = { 2 };

    find(array, 1, &one, &two);
    return 2 == one && 0 == two;
}

int test_two_elements() {
    int one = 0;
    int two = 0;
    int array[] = { 2, 3 };

    find(array, 2, &one, &two);
    return 3 == one && 2 == two;
}

int test_many_elements() {
    int one = 0;
    int two = 0;
    int array[] = {5, 2, 9, 5, 3, 1, 9, 2};

    find(array, 8, &one, &two);
    return 3 == one && 1 == two;
}

int test_negative_elements() {
    int one = 0;
    int two = 0;
    int array[] = {-5, -2, 9, -5, -3, 1, 9, -2};

    find(array, 8, &one, &two);
    return -3 == one && 1 == two;
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
    if (!test_two_elements()) {
        counter++;
        printf("Two elements test failed!\n");
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

