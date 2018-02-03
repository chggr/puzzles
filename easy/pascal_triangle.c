#include <stdio.h>

// Task description: Pascal's triangle is a triangular array of the binomial
// coefficients, as shown in the example below. The first and last element of
// each row is equal to one and elements in the middle are equal to the sum of
// the two numbers above them. Write a method that, given a row and a column,
// will return the value at that position;
//
// E.g. for position (0,0) the method should return 1
//      for position (3,2) the method should return 3
//
//                  1
//                1   1
//              1   2   1
//            1   3   3   1
//          1   4   6   4   1
//        1   5   10  10  5   1
//      1   6  15   20  15  6   1
//    1   7  21  35   35  21  7   1
//
// Solution: The implementation below uses a recursive approach to return the
// value in the Pascal's triangle for the given row and column. It first defines
// the base cases and builds on that to arrive to the final result. The runtime
// and space complexity of this implementation is O(2 ^ n), where n is the row.
// This is because the method calls itself twice in each recursive call.

int get(int row, int col) {
    if (row < 0 || col < 0 || col > row) return 0;
    if (col == 0 || col == row) return 1;
    return get(row - 1, col - 1) + get(row - 1, col);
}

int test_edges() {
    return 1 == get(0, 0) && 1 == get(1, 0) && 1 == get(1, 1) &&
           1 == get(2, 0) && 1 == get(2, 2) && 1 == get(3, 0) &&
           1 == get(3, 3) && 1 == get(100, 0) && 1 == get(100, 100);
}

int test_outside() {
    return 0 == get(-1, 0) && 0 == get(0, -1) && 0 == get(1, 3);
}

int test_middle() {
    return 2 == get(2, 1) && 3 == get(3, 1) && 3 == get(3, 2) &&
           4 == get(4, 1) && 6 == get(4, 2) && 4 == get(4, 3) &&
           5 == get(5, 1) && 10 == get(5, 2) && 10 == get(5, 3);
}

int main() {
    int counter = 0;
    if (!test_edges()) {
        printf("Edges test failed!\n");
        counter++;
    }
    if (!test_outside()) {
        printf("Outside test failed!\n");
        counter++;
    }
    if (!test_middle()) {
        printf("Middle test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

