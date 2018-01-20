#include <stdio.h>

// Task description: Given an array of integers, implement heapsort to sort the
// elements in place.
//
// E.g. for input array {8, 2, 9, 4, 0, 5, 1, 7, 6, 3}
//      the output should be {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//
// Solution: Heapsort is an in-place unstable sorting algorithm with best, worst
// and average runtime complexity of O(n * logn). The algorithm is divided into
// two parts:
//
// (1) A max heap is built out of the input data in place, mapping the structure
// of a complete binary tree into the array indices so that for each node its
// left child is at 2*n + 1 and its right child at 2*n + 2. The root node is
// stored at index 0.
//
// (2) The largest element of the heap (i.e. the root) is continuously removed
// and placed at the end of the array, thus dividing the array into a sorted and
// an unsorted region and iteratively shrinking the unsorted region until the
// whole array is sorted.
//
// The improvement heapsort offers versus insertion or selection sort is that it
// uses a heap data structure to identify the maximum element of the array in
// O(logn) rather than using a linear search in O(n). Although it is slower in
// practice than a well implemented quicksort, it has the advantage of a better
// worst-case complexity of O(n * logn) versus O(n^2).
//
// In the implementation below, method heapify() is used to turn the original
// array into a max heap. The parent node of each element is identified and
// method downheap() is used to bubble it down until it has reached the correct
// position in the heap. Once the max heap has been constructed, sorting the
// array is as simple as swapping the heap's root element with its last element
// and then calling downheap() to restore the heap's constraints.

void swap(int array[], int a, int b) {
    if (a == b) return;
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void downheap(int array[], int size, int parent) {
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;
    int max = parent;

    if (left < size && array[left] > array[max]) max = left;
    if (right < size && array[right] > array[max]) max = right;

    if (max != parent) {
        swap(array, parent, max);
        downheap(array, size, max);
    }
}

void heapify(int array[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        int parent = (i - 1) / 2;
        downheap(array, size, parent);
    }
}

void heapsort(int array[], int size) {
    heapify(array, size);

    for (int i = size - 1; i > 0; i--) {
        swap(array, 0, i);
        downheap(array, i, 0);
    }
}

int are_equal(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int test_heapify() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {9, 8, 6, 7, 4, 5, 2, 0, 3, 1};

    heapify(input, 10);
    return are_equal(input, expected, 10);
}

int test_heapsort_sorted() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    heapsort(input, 10);
    return are_equal(input, expected, 10);
}

int test_heapsort_reverse_sorted() {
    int input[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    heapsort(input, 10);
    return are_equal(input, expected, 10);
}

int test_heapsort_all_equal() {
    int input[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int expected[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    heapsort(input, 10);
    return are_equal(input, expected, 10);
}

int test_heapsort() {
    int input[] = {8, 2, 9, 4, 0, 5, 1, 7, 6, 3};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    heapsort(input, 10);
    return are_equal(input, expected, 10);
}

int main() {
    int counter = 0;
    if (!test_heapify()) {
        printf("Heapify test failed!\n");
        counter++;
    }
    if (!test_heapsort_sorted()) {
        printf("Heapsort already sorted test failed!\n");
        counter++;
    }
    if (!test_heapsort_reverse_sorted()) {
        printf("Heapsort already reverse sorted test failed!\n");
        counter++;
    }
    if (!test_heapsort_all_equal()) {
        printf("Heapsort all elements equal test failed!\n");
        counter++;
    }
    if (!test_heapsort()) {
        printf("Heapsort test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

