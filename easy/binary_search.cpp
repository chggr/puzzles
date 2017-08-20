#include <iostream>

// Task description: Given a sorted array of integers, implement a method to
// perform binary search and return a boolean indicating whether a given
// element is in the array or not.
//
// E.g. For input array {1, 2, 3} and element 4, it should return false.
//      For input array {1, 2, 3} and element 2, it should return true.

bool search(int array[], int start, int end, int element) {
	int len = end - start + 1;
	if (len == 0) return false;
	if (len == 1) return array[start] == element;

	int mid = array[start + len/2];
	if (mid == element) return true;
	if (mid < element) return search(array, start + len/2, end, element);
	else return search(array, start, end - len/2, element);
}

bool test_small_array_element_found() {
	int array[] = {1};
	return search(array, 0, 0, 1);
}

bool test_small_array_element_not_found() {
	int array[] = {1};
	return !search(array, 0, 0, 2);
}

bool test_big_array_element_found() {
	int array[] = {1,2,3,4,5};
	return search(array, 0, 4, 4);
}

bool test_big_array_element_not_found() {
	int array[] = {1,2,3,4,5};
	return !search(array, 0, 4, 7);
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

