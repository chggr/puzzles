#include <iostream>

// Task description: A greyscale image is represented by a NxN matrix where
// each pixel of the image is an integer value. Write a method to rotate the
// image by 90 degrees anti-clockwise. Do not use any additional storage, the
// transformation should be done in place.
//
// E.g. For the following image, the method should return:
//
//      1 2 3        3 6 9
//      4 5 6  ===>  2 5 8
//      7 8 9        1 4 7

int get(int* matrix, int n, int i, int j) {
    return matrix[n*i + j];
}

void put(int* matrix, int n, int i, int j, int value) {
    matrix[n*i + j] = value;
}

void rotate(int* matrix, int n) {
    if (n == 0) return;

    for (int row = 0; row < (n + 1) / 2; row ++) {
        for (int column = row; column < n-row-1; column++) {
            int tempA = get(matrix, n, row, column);
            int tempB = get(matrix, n, n-column-1, row);
            int tempC = get(matrix, n, n-row-1, n-column-1);
            int tempD = get(matrix, n, column, n-row-1);

            put(matrix, n, n-column-1, row, tempA);
            put(matrix, n, n-row-1, n-column-1, tempB);
            put(matrix, n, column, n-row-1, tempC);
            put(matrix, n, row, column, tempD);
        }
    }
}

bool are_equal(int* a, int* b, int n) {
    for (int i = 0; i < n * n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool test_3x3_array() {
    int input[] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9};

    int expected[] = {3, 6, 9,
                      2, 5, 8,
                      1, 4, 7};

    rotate(input, 3);
    return are_equal(input, expected, 3);
}

bool test_4x4_array() {
    int input[] = {1,  2,  3,  4,
                   5,  6,  7,  8,
                   9,  10, 11, 12,
                   13, 14, 15, 16};

    int expected[] = {4, 8, 12, 16,
                      3, 7, 11, 15,
                      2, 6, 10, 14,
                      1, 5,  9, 13};

    rotate(input, 4);
    return are_equal(input, expected, 4);
}

bool test_5x5_array() {
    int input[] = {1,  2,  3,  4,  5,
                   6,  7,  8,  9,  10,
                   11, 12, 13, 14, 15,
                   16, 17, 18, 19, 20,
                   21, 22, 23, 24, 25};

    int expected[] = {5, 10, 15, 20, 25,
                      4,  9, 14, 19, 24,
                      3,  8, 13, 18, 23,
                      2,  7, 12, 17, 22,
                      1,  6, 11, 16, 21};

    rotate(input, 5);
    return are_equal(input, expected, 5);
}

int main() {
    int counter = 0;
    if (!test_3x3_array()) {
        std::cout << "3x3 array test failed!\n";
        counter++;
    }
    if (!test_4x4_array()) {
        std::cout << "4x4 array test failed!\n";
        counter++;
    }
    if (!test_5x5_array()) {
        std::cout << "5x5 array test failed!\n";
        counter++;
    }
    std::cout << counter << " tests failed.\n";
}

