#include <stdio.h>
#include <stdlib.h>

// Task description: Write a function in C to allocate memory for a two
// dimensional array, minimizing the number of calls to malloc as much as
// possible. The memory should be accessible using notation: array[i][j].
//
// Solution: A two dimensional array is basically an array of arrays and
// therefore we will need to use a double pointer to point to it (e.g. int**).
//
// The first implementation below is the most obvious solution. A 1D array of
// pointers is initially created and for each index we allocate a new 1D array
// of elements. The opposite process will need to be followed in order to free
// the memory. This solution involves in total 1 + rows calls to malloc() and
// free().
//
// The second implementation is much more efficient and uses only a single call
// to malloc() and the memory can be released with a single call to free(). The
// total memory requirement (header + data) is initially calculated and malloc()
// is called once to allocate the memory as a single block. Then the contents
// of the memory locations in the header are updated to point to the start of
// each row in the data segment.

int** alloc2d(int rows, int cols) {
    int** ptr = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        ptr[i] = malloc(cols * sizeof(int));
    }
    return ptr;
}

void free2d(int** ptr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

int** alloc2d_opt(int rows, int cols) {
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int** ptr = malloc(header + data);
    if (ptr == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        ptr[i] = (int*) (ptr + rows) + i * cols;
    }
    return ptr;
}

int test_2d_array(int** ptr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ptr[i][j] = i * j;
        }
    }

    int ret = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ret = ret && (ptr[i][j] == i * j);
        }
    }
    return ret;
}

int test_alloc2d() {
    int** ptr = alloc2d(10, 10);
    int ret = test_2d_array(ptr, 10, 10);
    free2d(ptr, 10);
    return ret;
}

int test_alloc2d_opt() {
    int** ptr = alloc2d_opt(10, 10);
    int ret = test_2d_array(ptr, 10, 10);
    free(ptr);
    return ret;
}

int main() {
    int counter = 0;
    if (!test_alloc2d()) {
        printf("Alloc 2d test failed!\n");
        counter++;
    }
    if (!test_alloc2d_opt()) {
        printf("Optimized alloc 2d test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

