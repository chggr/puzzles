#include <stdio.h>

// Task description: Given an array of integers, implement the merge sort
// algorithm to sort the contents of the array in place in ascending order.
//
// E.g. Input array {9, -2, 4} should be sorted as {-2, 4, 9}.
//
// Solution: The merge sort algorithm divides the input array in half, sorts
// the two halves and then merges them back together. This is executed
// recursively until the full array is sorted. The runtime complexity of this
// algorithm is O(n logn) and the space complexity is O(n). Note that during
// merge() the remaining elements of only the left half of the array need to
// be copied into the target array. Any remaining elements of the right half
// of the array would already be in place in the target array.

void merge(int input[], int temp[], int low, int mid, int high) {
    for (int i = low; i <= high; i++) {
        temp[i] = input[i];
    }

    int left = low;
    int right = mid + 1;
    int current = low;
    while (left <= mid && right <= high) {
        if (temp[left] <= temp[right]) {
            input[current++] = temp[left++];
        } else {
            input[current++] = temp[right++];
        }
    }

    while (left <= mid) {
        input[current++] = temp[left++];
    }
}

void sort(int input[], int temp[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sort(input, temp, low, mid);
        sort(input, temp, mid + 1, high);
        merge(input, temp, low, mid, high);
    }
}

void merge_sort(int input[], int size) {
    int temp[size];
    sort(input, temp, 0, size - 1);
}

int is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return 0;
    }
    return 1;
}

int main() {
    int input[] = {0, -1, -2, -1, 10, 3, 8};
    merge_sort(input, 7);
    if (!is_sorted(input, 7)) {
        printf("Input array has not been sorted!\n");
    } else {
        printf("Input array is sorted.\n");
    }
}

