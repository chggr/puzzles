#include <stdio.h>

// Task description: Given an unsorted array of integers, write a method to
// compute the number of inversions. This indicates how far the array is from
// being sorted. If the array is already sorted, the inversion count is zero.
//
// E.g. for input array {1, 5, 2, 4, 3}
//      the inversions are: (5, 2), (5, 4), (5, 3), (4, 3)
//      therefore the inversion count is 4
//
// Solution: The first implementation below is a brute force approach where for
// each element in the array we count the number of elements after it that are
// less. The runtime complexity of this approach is O(N^2) where N is the length
// of the array and the space complexity is O(1).
//
// The second implementation uses a modified merge sort to count the number of
// inversions. This has the side effect of also sorting the input array. The
// number of inversions at each recursive step will be equal to the sum of the
// inversions when sorting the left sub-array, the inversions when sorting the
// right sub-array and the inversions encountered when merging the two. The
// runtime complexity of this approach is O(N * logN), but the space complexity
// is O(N) because of the auxiliary array during the merge step.
//
// In more detail, during the merge step we also need to keep track and return
// the inversion count. If the current element from the right sub-array is less
// than the current element from the left sub-array, the inversion count will
// be incremented by mid - left + 1. This is because in that case all remaining
// elements from the left sub-array will also be greater than the element from
// the right sub-array and therefore will constitute inversions.

int count(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[i]) result++;
        }
    }
    return result;
}

// Modified merge step of merge-sort to return the inversion count.
int merge(int array[], int from, int mid, int to) {

    int aux[to - from + 1];

    int left = from;
    int right = mid + 1;
    int idx = 0;
    int count = 0;

    // Merge the two sub-arrays, keeping track of inversion count.
    while (left <= mid && right <= to) {
        if (array[left] < array[right]) {
            aux[idx++] = array[left++];
        } else {
            aux[idx++] = array[right++];
            count += mid - left + 1;
        }
    }

    // Copy any remaining elements.
    while (left <= mid) aux[idx++] = array[left++];
    while (right <= to) aux[idx++] = array[right++];

    // Copy results from the auxiliary array back to the array.
    for (int i = from; i <= to; i++) {
        array[i] = aux[i - from];
    }

    return count;
}

int sort(int array[], int from, int to) {
    if (from >= to) return 0;

    int count = 0;
    int mid = (from + to) / 2;
    count += sort(array, from, mid);
    count += sort(array, mid + 1, to);
    count += merge(array, from, mid, to);

    return count;
}

int count_opt(int array[], int size) {
    return sort(array, 0, size - 1);
}

int test_empty_array() {
    int array[] = {};
    return 0 == count(array, 0) &&
           0 == count_opt(array, 0);
}

int test_no_inversions() {
    int array[] = {1, 2, 3, 4, 5};
    return 0 == count(array, 5) &&
           0 == count_opt(array, 5);
}

int test_inversions() {
    int array[] = {1, 5, 2, 4, 3};
    return 4 == count(array, 5) &&
           4 == count_opt(array, 5);
}

int main() {
    int counter = 0;
    if (!test_empty_array()) {
        counter++;
        printf("Empty array test failed!\n");
    }
    if (!test_no_inversions()) {
        counter++;
        printf("No inversions test failed!\n");
    }
    if (!test_inversions()) {
        counter++;
        printf("Inversions test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

