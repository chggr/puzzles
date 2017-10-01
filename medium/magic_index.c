#include <math.h>
#include <stdio.h>

// Task description: In an array A[n], a magic index is defined as the index
// where A[i] = i. Given that the array is sorted, write a method to find a
// magic index if one exists. Do not assume that the array has distinct
// elements.
//
// Solution: The simplest approach would be to iterate through all elements in
// the array and for each element check whether A[i] == i. The complexity of
// this solution is O(n), which makes it very expensive for larger arrays,
// especially since we know that the array is sorted.
//
// The second approach would be to use binary search and therefore reduce the
// runtime complexity to O(logn), taking advantage of the fact that the array
// is already sorted. This works well if the elements are distinct, but fails
// when the array contains duplicates.
//
// The implementation below is a variation of the binary search algorithm that
// caters for arrays with duplicate elements. During binary search, both left
// and right sides are checked to catch any duplicates. If the array does not
// contain any duplicates, this implementation is similar to simple binary
// search.

int magic_index(int *array, int start, int end) {
    if (end < start) return -1;

    int middle = (start + end) / 2;
    if (array[middle] == middle) return middle;

    int min = array[middle] < middle - 1 ? array[middle] : middle - 1;
    int left = magic_index(array, start, min);

    int max = array[middle] > middle + 1 ? array[middle] : middle + 1;
    int right = magic_index(array, max, end);

    return right == -1 ? left : right;
}

int test_magic_index() {
    int array[] = {-2, -1, 0, 2, 4, 15};
    return 4 == magic_index(array, 0, 5);
}

int test_magic_index_at_start() {
    int array[] = {0, 5, 7, 10, 13};
    return 0 == magic_index(array, 0, 4);
}

int test_magic_index_at_end() {
    int array[] = {-1, 0, 1, 2, 4};
    return 4 == magic_index(array, 0, 4);
}

int test_no_magic_index() {
    int array[] = {-2, -1, 0, 1, 2, 3};
    return -1 == magic_index(array, 0, 5);
}

int test_magic_index_duplicates() {
    int array[] = {-1, 0, 2, 2, 3, 3, 3, 3, 20};
    return 2 == magic_index(array, 0, 8);
}

int main() {
    int counter = 0;
    if (!test_magic_index()) {
        printf("Magic index test failed!\n");
        counter++;
    }
    if (!test_magic_index_at_start()) {
        printf("Magic index at start test failed!\n");
        counter++;
    }
    if (!test_magic_index_at_end()) {
        printf("Magic index at end test failed!\n");
        counter++;
    }
    if (!test_no_magic_index()) {
        printf("No magic index test failed!\n");
        counter++;
    }
    if (!test_magic_index_duplicates()) {
        printf("Magic index with duplicates test failed!\n");
        counter++;
    }
    printf("%d tests failed!\n", counter);
}

