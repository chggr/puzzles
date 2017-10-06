#include <stdio.h>

// Task description: Given an 8x8 chess board, write a method to print all
// possible ways of arranging eight queens so that none of them share the
// same row, column or diagonal.
//
// Solution: The implementation below uses an iterative approach to print out
// all possible chess board configurations with 8 queens. It starts by placing
// a queen in the first row and then moves on recursively to place queens in
// the remaining rows as well. This implementation is using an 8x8 matrix to
// store the state of the chess board, but this can be optimized by storing a
// single 8 byte array where array[r] = c indicates that row r has queen at
// column c.

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

void place(int* board, int row) {
    if (row >= 8) {
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
}

