#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task description: A system is generating a stream of positive integers and
// we would like to store these integers in memory in ascending order. Write
// code to store the incoming integers in two data structures: (a) Singly
// linked list and (b) pre-allocated array without need for resizing.
//
// Which data structure do you expect to perform better? Compare the performance
// for different input sizes and explain the actual results.
//
// Solution: Storing the incoming integers in a sorted, singly linked list
// requires O(n/2) to find the right spot to insert each integer and O(1) to
// actually perform the insertion. Thus the overal complexity is O(n) (linear)
// for the linked list (linear).
//
// On the contrary, storing an integer in a sorted array requires O(n/2) to
// find the right spot to insert it, O(n/2) to shift all data after the
// insertion point by one position and O(1) to do the insertion. Thus the
// overall complexity for the array is O(n^2) (quadratic).
//
// The analysis above indicates that a linked list has a significal performance
// advantage compared to an array. This does not translate well in practice
// though, as the results below demonstrate! For small sizes, indeed the list
// seems to be a better solution than the array. As the size grows though, the
// array starts outperforming the list due to spatial data locality. Data
// compactness allows the array to maximize its L3 / L2 cache hits thus
// resulting in much better performance. On the other hand, the linked list is
// jumping from one memory location to another, thus incurring multiple cache
// misses that tax its performance significantly.
//
// Please note that we would get similar results even if we factor out the
// extra memory allocations that the linked list solution involves.
//
// Results:
//
// Running test with size: 1
// Adding to list took: 1
// Adding to array took: 1 
//
// Running test with size: 10
// Adding to list took: 1
// Adding to array took: 2
//
// Running test with size: 100
// Adding to list took: 15
// Adding to array took: 10
//
// Running test with size: 1000
// Adding to list took: 661
// Adding to array took: 380
//
// Running test with size: 10000
// Adding to list took: 220785
// Adding to array took: 34925

struct node {
	int value;
	struct node *next;
};

struct node *head = NULL;
int *array = NULL;
int array_size = 0;

void add_list(int value) {
	struct node *new_node = malloc(sizeof *new_node);
	new_node->value = value;

	if (head == NULL) {
		head = new_node;
		return;
	}

	struct node* curr = head;
	struct node* prev = NULL;
	while (curr && curr->value < value) {
		prev = curr;
		curr = curr->next;
	}
	if (!prev) {
		head = new_node;
		new_node->next = curr;
	} else {
		prev->next = new_node;
		new_node->next = curr;
	}
}

void free_list() {
	struct node* curr = head;
	struct node* next;
	head = NULL;

	while (curr) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void add_array(int value) {
	int pos;
	for (pos = 0; pos < array_size; pos++) {
		if (array[pos] > value) break;
	}

	for (int i = array_size; i >= pos; i--) {
		array[i] = array[i-1];
	}
	array[pos] = value;
}

int assert_correctness() {
	for (int i = 0; i < array_size - 1; i++) {
		if (array[i] > array[i + 1]) return 0;
	}

	struct node* current = head;
	int i = 0;
	while(current) {
		if (current->next && current->next->value < current->value)
			return 0;
		if (current->value != array[i++])
			return 0;
		current = current->next;
	}
	return 1;
}

int * create_random(int size) {
	int *result = malloc(size * sizeof *result);
	srand(clock());
	for (int i = 0; i < size; i++) {
		result[i] = rand();
	}
	return result;
}

void run_test(unsigned int size) {
	printf("Running test with size: %u\n", size);

	array = malloc(size * sizeof *array);
	array_size = 0;
	int *random = create_random(size);

	clock_t start = clock();
	for (int i = 0; i < size; i++) {
		add_list(random[i]);
	}
	printf("Adding to list took: %ld\n", (clock() - start));

	start = clock();
	for (int i = 0; i < size; i++) {
		add_array(random[i]);
		++array_size;
	}
	printf("Adding to array took: %ld\n\n", (clock() - start));

	if (!assert_correctness(head)) {
		printf("Values are not ordered in list or array!");
	}

	free(array);
	free(random);
	free_list();
}

int main() {
	run_test(1);
	run_test(10);
	run_test(100);
	run_test(1000);
	run_test(10000);
}

