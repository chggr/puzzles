#include <iostream>
#include <vector>

// Task description: Given an MxN matrix of integers, write a method that will
// detect if an element is zero and will zero out its entire row and column.
//
// E.g. For the following matrix, the method should return:
//
//            1 2 3         0 2 3
//            0 5 6   ==>   0 0 0
//            7 8 9         0 8 9

void zero_matrix(int* matrix, int m, int n) {
    std::vector<int> rows;
    std::vector<int> columns;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i * m + j] == 0) {
                rows.push_back(i);
                columns.push_back(j);
            }
        }
    }

    // Zero out the rows.
    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < n; j++) {
            matrix[rows.at(i) * m + j] = 0;
        }
    }

    // Zero out the columns.
    for (int j = 0; j < columns.size(); j++) {
        for (int i = 0; i < m; i++) {
            matrix[i * m + columns.at(j)] = 0;
        }
    }
}

bool are_equal(int* a, int* b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool test_no_zero() {
    int input[] = {1,2,3,4,5,6,7,8,9};
    int expected[] = {1,2,3,4,5,6,7,8,9};
    zero_matrix(input, 3, 3);
    return are_equal(input, expected, 9);
}

bool test_one_zero() {
    int input[] = {1,2,3,0,5,6,7,8,9};
    int expected[] = {0,2,3,0,0,0,0,8,9};
    zero_matrix(input, 3, 3);
    return are_equal(input, expected, 9);
}

bool test_diagonal_zero() {
    int input[] = {0,2,3,4,0,6,7,8,0};
    int expected[] = {0,0,0,0,0,0,0,0,0};
    zero_matrix(input, 3, 3);
    return are_equal(input, expected, 9);
}

int main() {
    int counter = 0;
    if (!test_no_zero()) {
        std::cout << "No zero test failed!" << std::endl;
        counter++;
    }
    if (!test_one_zero()) {
        std::cout << "One zero test failed!" << std::endl;
        counter++;
    }
    if (!test_diagonal_zero()) {
        std::cout << "Diagonal zero test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

