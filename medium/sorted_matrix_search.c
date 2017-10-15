#include <stdio.h>

// Task description: Given an MxN matrix in which each row and each column are
// sorted in ascending order, write a method to search for an element.
//
// E.g. for input matrix: 12 32 45 61 78
//                        15 34 47 79 81
//                        21 42 51 82 87
//                        33 54 63 94 99
//
//      the method should return true for 82 but false for 13.
//
// Solution: The simplest approach would be to do a binary search in each row.
// The complexity of this solution would be O(M * logN) because we would need
// to do M binary searches and each would require O(logN). This approach is
// simple but inefficient, because the data is sorted across both dimensions
// and it takes advantage of only one.
//
// The implementation below takes advantage of the observation that the first
// element in each column is the smallest element of the column and the last
// element in each row is the largest element of the row. It starts at the top
// right corner of the matrix and uses this observation to work its way through
// to the given element.
//
// An alternative approach would be to use binary search across the two
// dimensions of the matrix. This is based on the observation that for each
// element (i, i) in the diagonal:
//
// - numbers less than that will be located inside the box defined by:
//   [(0, 0), (0, i), (i, 0), (i, i)].
//
// - numbers greater than that will be located inside the box defined by:
//   [(i, i), (m, i), (i, n), (m, n)].
//
// Therefore based on the observations above we could perform a binary search
// across the diagonal, partitioning our matrix into quadrants and recursively
// searching into these quadrants.

int get(int array[], int n, int row, int col) {
    return array[row * n + col];
}

int find(int* array, int m, int n, int elem) {
    int row = 0;
    int col = n - 1;
    int val;

    while (row < n && col >= 0) {
        val = get(array, n, row, col);
        if (val == elem) {
            return 1;
        } else if (val > elem) {
            col--;
        } else {
            row++;
        }
    }

    return 0;
}

int test_not_found() {
    int array[] = { 12, 32, 45, 61, 78,
                    15, 34, 47, 79, 81,
                    21, 42, 51, 82, 87,
                    33, 54, 63, 94, 99 };
    return !find(array, 4, 5, 13);
}

int test_found() {
    int array[] = { 12, 32, 45, 61, 78,
                    15, 34, 47, 79, 81,
                    21, 42, 51, 82, 87,
                    33, 54, 63, 94, 99 };
    return find(array, 4, 5, 42);
}

int main() {
    int counter = 0;
    if (!test_not_found()) {
        printf("Not found test failed!\n");
        counter++;
    }
    if (!test_found()) {
        printf("Found test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

