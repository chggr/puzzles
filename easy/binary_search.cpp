#include <iostream>

// Task description: Given a sorted array of integers, implement a method to
// perform binary search and return a boolean indicating whether a given
// element is in the array or not.
//
// E.g. For input array {1, 2, 3} and element 4, it should return false.
//      For input array {1, 2, 3} and element 2, it should return true.
//
// Solution: Binary search can be implemented either recursively or iteratively.
// The first implementation below is recursive, with O(logn) runtime and space
// complexities. The second implementation is iterative, with O(logn) runtime
// complexity but O(1) space complexity.

bool search(int array[], int start, int end, int element) {
    int len = end - start + 1;
    if (len == 0) return false;
    if (len == 1) return array[start] == element;

    int mid = array[start + len/2];
    if (mid == element) return true;
    if (mid < element) return search(array, start + len/2, end, element);
    else return search(array, start, end - len/2, element);
}

bool search_it(int array[], int size, int element) {
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (array[mid] < element) {
            low = mid + 1;
        } else if (array[mid] > element) {
            high = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

bool test_small_array_element_found() {
    int array[] = {1};
    return search(array, 0, 0, 1) &&
           search_it(array, 1, 1);
}

bool test_small_array_element_not_found() {
    int array[] = {1};
    return !search(array, 0, 0, 2) &&
           !search_it(array, 1, 2);
}

bool test_big_array_element_found() {
    int array[] = {1,2,3,4,5};
    return search(array, 0, 4, 4) &&
           search_it(array, 5, 4);
}

bool test_big_array_element_not_found() {
    int array[] = {1,2,3,4,5};
    return !search(array, 0, 4, 7) &&
           !search_it(array, 5, 7);
}

int main() {
    int counter = 0;
    if (!test_small_array_element_found()) {
        std::cout << "Small array, element found test failed!\n";
        counter++;
    }
    if (!test_small_array_element_not_found()) {
        std::cout << "Small array, element not found test failed!\n";
        counter++;
    }
    if (!test_big_array_element_found()) {
        std::cout << "Big array, element found test failed!\n";
        counter++;
    }
    if (!test_big_array_element_not_found()) {
        std::cout << "Big array, element not found test failed!\n";
        counter++;
    }
    std::cout << counter << " tests failed.\n";
}

