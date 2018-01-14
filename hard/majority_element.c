#include <stdio.h>

// Task description: A majority element is an element that makes up more than
// half the items in an array. Given an array of positive integers, write a
// method to return the majority element if it exists or -1 if it does not. The
// runtime complexity of the solution should be O(N) and the space complexity
// O(1).
//
// E.g. for array {1, 2, 5, 9, 5, 9, 5, 5, 5}
//      the method should return 5
//
//      for array {1, 2, 5, 9, 4, 9, 5, 3, 5}
//      the method should return -1
//
// Solution: A brute force solution would be to go through each element and
// count its occurrences in the given array. If the number of occurrences is
// greater than array_size / 2, then this is the majority element. The space
// complexity of this approach is O(1) but the runtime complexity is O(N^2).
// This clearly does not satisfy the requirements.
//
// The implementation below starts by picking the first element in the array
// and goes through the remaining array keeping track of the element's balance,
// i.e. how many times it has appeared minus how many times it has not. If the
// balance drops to zero, it means that for the sub-array up to now there is no
// majority element. In this case the algorithm picks up the next element and
// continues using that. Once a possible majority element has been found, there
// is a final check that this is indeed the majority element. The runtime
// complexity of this approach is O(N) and its space complexity is O(1), which
// satisfies the task's requirements.

int maj_elem(int array[], int size) {
    if (size == 0) return -1;

    int elem = array[0];
    int bal = 1;
    for (int i = 1; i < size; i++) {
        if (bal == 0) {
            elem = array[i];
            bal = 1;
        } else {
            if (array[i] == elem) bal++;
            else bal--;
        }
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        count += array[i] == elem;
    }

    return count > (size / 2) ? elem : -1;
}

int test_empty_array() {
    return -1 == maj_elem(NULL, 0);
}

int test_maj_elem_odd() {
    int array[] = {1, 2, 5, 9, 5, 9, 5, 5, 5};
    return 5 == maj_elem(array, 9);
}

int test_no_maj_elem_odd() {
    int array[] = {1, 2, 5, 9, 4, 9, 5, 3, 5};
    return -1 == maj_elem(array, 9);
}

int test_maj_elem_even() {
    int array[] = {1, 5, 2, 5, 9, 5, 9, 5, 5, 5};
    return 5 == maj_elem(array, 10);
}

int test_no_maj_elem_even() {
    int array[] = {1, 5, 2, 5, 9, 5, 9, 5, 1, 5};
    return -1 == maj_elem(array, 10);
}

int main() {
    int counter = 0;
    if (!test_empty_array()) {
        printf("Empty array test failed!\n");
        counter++;
    }
    if (!test_maj_elem_odd()) {
        printf("Majority element odd test failed!\n");
        counter++;
    }
    if (!test_no_maj_elem_odd()) {
        printf("No majority element odd test failed!\n");
        counter++;
    }
    if (!test_maj_elem_even()) {
        printf("Majority element even test failed!\n");
        counter++;
    }
    if (!test_no_maj_elem_even()) {
        printf("No majority element even test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

