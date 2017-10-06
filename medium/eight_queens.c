#include <stdio.h>

// Task description: Given an 8x8 chess board, write a method to print all
// possible ways of arranging eight queens so that none of them share the
// same row, column or diagonal.
//
// Solution: The implementation below uses an iterative approach to print out
// all possible chess board configurations with 8 queens. It starts by placing
// a queen in the first row and then moves on recursively to place queens in
// the remaining rows as well.
//
// The second implementation is an optimization on the first one in two ways:
// (1) it does not use an 8x8 matrix but rather a one-dimensional 8 element
// array to store the chess board's state, where array[r] = c indicates that
// row r has a queen at column c. (2) it does not check whether each row is
// free, as the algorithm attempts to place a queen at a given row only once.

void print_board(int *board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", board[i * 8 + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_row_free(int *board, int row) {
    for (int i = 0; i < 8; i++) {
        if (board[row * 8 + i]) {
            return 0;
        }
    }
    return 1;
}

int is_col_free(int *board, int col) {
    for (int i = 0; i < 8; i++) {
        if (board[i * 8 + col]) {
            return 0;
        }
    }
    return 1;
}

int is_diag_free(int *board, int row, int col) {
    for (int i = 0; i < 8; i++) {
        if (row - i >= 0 && col - i >= 0 &&
            board[(row - i) * 8 + col - i]) {
            return 0;
        }
        if (row + i < 8 && col + i < 8 &&
            board[(row + i) * 8 + col + i]) {
            return 0;
        }
        if (row - i >= 0 && col + i < 8 &&
            board[(row - i) * 8 + col + i]) {
            return 0;
        }
        if (row + i < 8 && col - i >= 0 &&
            board[(row + i) * 8 + col - i]) {
            return 0;
        }
    }
    return 1;
}

int can_place(int *board, int row, int col) {
    return is_col_free(board, col) &&
           is_row_free(board, row) &&
           is_diag_free(board, row, col);
}

void place(int *board, int row) {
    if (row == 8) {
        print_board(board);
        return;
    }

    for (int i = 0; i <= 8; i++) {
        if (can_place(board, row, i)) {
            board[row * 8 + i] = 1;
            place(board, row + 1);
            board[row * 8 + i] = 0;
        }
    }
}

int can_place_opt(int *array, int row, int col) {
    for (int r = 0; r < row; r++) {

        // Check if the column has been used already.
        int c = array[r];
        if (col == c) return 0;

        // Check diagonals: if the distance between rows is the same as
        // distance between columns, then they are in same diagonal.
        int dist = c - col;
        dist = dist < 0 ? -dist : dist;
        if (dist == row - r) return 0;
    }
    return 1;
}

void place_opt(int *array, int row) {
    if (row == 8) {
        for (int i = 0; i < 8; i++) {
            printf("%d ", array[i]);
        }
        printf("\n\n");
        return;
    }

    for (int col = 0; col < 8; col++) {
        if (can_place_opt(array, row, col)) {
            array[row] = col;
            place_opt(array, row + 1);
        }
    }
}

int test_is_row_free() {
    int board[64] = {0};
    board[8] = 1;
    return is_row_free(board, 0) &&
           !is_row_free(board, 1) &&
           is_row_free(board, 2) &&
           is_row_free(board, 3) &&
           is_row_free(board, 4) &&
           is_row_free(board, 5) &&
           is_row_free(board, 6) &&
           is_row_free(board, 7);
}

int test_is_col_free() {
    int board[64] = {0};
    board[3] = 1;
    return is_col_free(board, 0) &&
           is_col_free(board, 1) &&
           is_col_free(board, 2) &&
           !is_col_free(board, 3) &&
           is_col_free(board, 4) &&
           is_col_free(board, 5) &&
           is_col_free(board, 6) &&
           is_col_free(board, 7);
}

int test_is_diag_free() {
    int board[64] = {0};
    board[3 * 8 + 3] = 1;
    return !is_diag_free(board, 0, 0) &&
           !is_diag_free(board, 1, 1) &&
           !is_diag_free(board, 2, 2) &&
           !is_diag_free(board, 3, 3) &&
           !is_diag_free(board, 4, 4) &&
           !is_diag_free(board, 5, 5) &&
           !is_diag_free(board, 6, 6) &&
           !is_diag_free(board, 7, 7) &&
           !is_diag_free(board, 6, 0) &&
           !is_diag_free(board, 5, 1) &&
           !is_diag_free(board, 4, 2) &&
           !is_diag_free(board, 3, 3) &&
           !is_diag_free(board, 2, 4) &&
           !is_diag_free(board, 1, 5) &&
           !is_diag_free(board, 0, 6) &&
           is_diag_free(board, 1, 0);
}

int main() {
    int counter = 0;
    if (!test_is_row_free()) {
        printf("Is row free test failed!\n");
        counter++;
    }
    if (!test_is_col_free()) {
        printf("Is col free test failed!\n");
        counter++;
    }
    if (!test_is_diag_free()) {
        printf("Is diag free test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);

    int board[64] = {0};
    place(board, 0);

    int array[8] = {0};
    place_opt(array, 0);
}

