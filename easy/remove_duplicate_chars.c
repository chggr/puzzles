#include <stdio.h>
#include <string.h>

// Task description: Given a classic C-Style string, write a method to remove
// all duplicate characters in it without using any additional storage. The
// operation needs to be performed in place and the characters should retain
// their order.
//
// E.g. For input string \0, the method should return \0.
//      For input string abc\0, the method should return abc\0.
//      For input string abbcc\0, the method should return abc\0.

void remove_duplicates(char *input) {
	if (!input) return;

	char *current = input;
	char *last = input;
	while (*(++current)) {
		char *temp = input;
		while (temp <= last && *temp != *current) temp++;
		if (temp == last + 1) {
			*(++last) = *current;
		}
	}
	*(++last) = 0;
}

int test_empty_input() {
	char input[] = "";
	remove_duplicates(input);
	return strcmp(input, "") == 0;
}

int test_no_duplicates() {
	char input[] = "abc";
	remove_duplicates(input);
	return strcmp(input, "abc") == 0;
}

int test_with_duplicates() {
	char input[] = "aabbcc";
	remove_duplicates(input);
	return strcmp(input, "abc") == 0;
}

int test_only_duplicates() {
	char input[] = "aaaa";
	remove_duplicates(input);
	return strcmp(input, "a") == 0;
}

void main() {
	int counter = 0;
	if (!test_empty_input()) {
		printf("Empty input test failed!\n");
		counter++;
	}
	if (!test_no_duplicates()) {
		printf("No duplicates test failed!\n");
		counter++;
	}
	if (!test_with_duplicates()) {
		printf("With duplicates test failed!\n");
		counter++;
	}
	if (!test_only_duplicates()) {
		printf("Only duplicates test failed!\n");
		counter++;
	}
	printf("%d tests failed!\n", counter);
}

