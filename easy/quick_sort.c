#include <stdio.h>

// Task description: Given an array of integers, implement the quick sort
// algorithm to sort the contents of the array in place in ascending order.
//
// E.g. Input array {1, -1, 0} should be sorted as {-1, 0, 1}.
//
// Solution: The quick sort algorithm first picks up a random element and
// partitions the input array so that all elements less than the partitioning
// element come before all elements greater than it. Partitioning is carried
// out efficiently through a series of swaps. This approach is applied
// recursively until the whole input array is sorted. The average runtime
// complexity of this algorithm is O(n logn) but the worst case complexity is
// O(n^2). Space complexity is O(logn) due to the recursive method calls.

void swap(int input[], int a, int b) {
    if (a == b) return;
    int temp = input[a];
    input[a] = input[b];
    input[b] = temp;
}

int partition(int input[], int low, int high) {
    int pivot = input[(low + high) / 2];

    while (low <= high) {
        while (input[low] < pivot) low++;
        while (input[high] > pivot) high--;

        if (low <= high) {
            swap(input, high, low);
            high--;
            low++;
        }
    }
    return low;
}

int quick_sort(int input[], int low, int high) {
    int index = partition(input, low, high);
    if (low < index - 1) quick_sort(input, low, index - 1);
    if (high > index) quick_sort(input, index, high);
}

int is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return 0;
    }
    return 1;
}

void main() {
    int input[] = {0, -1, -2, -1, 10, 3, 8};
    quick_sort(input, 0, 6);

    if (!is_sorted(input, 7)) {
        printf("Input array has not been sorted!\n");
    } else {
        printf("Input array is sorted.\n");
    }
}

