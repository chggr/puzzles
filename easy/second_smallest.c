#include <stdio.h>

// Task description: Given an array of integers, write a method that will
// return the second largest integer in the array. If the given input array
// contains less than two elements, the method should return zero. The method
// should also cater for cases where the given array contains duplicate
// elements.
//
// E.g. For input array {1} the method should return 0
//      For input array {1, 2, 3} the method should return 2
//      For input array {1, 1, 2} the method should return 2

int second_smallest(int input[], int size)
{
	if (!input || size < 2) return 0;

	int min = input[0];
	int min2 = input[0];
	for (int i=0; i<size; i++) {
		if (input[i] < min) {
			min2 = min;
			min = input[i];
		} else if (input[i] != min && input[i] < min2) {
			min2 = input[i];
		}
	}
	return min2;
}

int test_empty_input()
{
	return second_smallest(NULL, 0) == 0;
}

int test_one_element()
{
	int input[] = {0};
	return second_smallest(input, 1) == 0;
}

int test_two_elements() {
	int input[] = {1, 0};
	return second_smallest(input, 2) == 1;
}

int test_negative_numbers() {
	int input[] = {-10, 23, -99, -125, 1};
	return second_smallest(input, 5) == -99;
}

int test_duplicate_numbers() {
	int input[] = {67, -33, 67, 70, -33};
	return second_smallest(input, 5) == 67;
}

void main()
{
	int counter = 0;
	if (!test_empty_input()) {
		counter++;
		printf("Empty input test failed!\n");
	}
	if (!test_one_element()) {
		counter++;
		printf("One element test failed!\n");
	}
	if (!test_two_elements()) {
		counter++;
		printf("Two elements test failed!\n");
	}
	if (!test_negative_numbers()) {
		counter++;
		printf("Negative numbers test failed!\n");
	}
	if (!test_duplicate_numbers()) {
		counter++;
		printf("Duplicate numbers test failed!\n");
	}
	printf("%d tests failed.\n", counter);
}

