#include <iostream>

// Task description: Write a method to solve a sudoku puzzle.
//
// Solution: The implementation below is using a simple recursive approach
// with backtracking to solve a sudoku puzzle. In each recursion we first check
// whether there are any empty positions in the sudoku. If there are no empty
// positions, then the sudoku has already been solved and the method returns
// true. Otherwise we pick the first empty position and attempt to solve it by
// assigning possible numbers and checking whether each assignment leads to a
// valid board and can recursively lead to a solution. The method returns false
// if all possible solutions have been tried and have been unsuccessful.

bool isRowValid(int s[9][9], int row) {
    bool seen[9] = {false};
    for (int i = 0; i < 9; i++) {
        if (s[row][i] == 0) continue;
        if (seen[s[row][i] - 1]) return false;
        seen[s[row][i] - 1] = true;
    }
    return true;
}

bool isColValid(int s[9][9], int col) {
    bool seen[9] = {false};
    for (int i = 0; i < 9; i++) {
        if (s[i][col] == 0) continue;
        if (seen[s[i][col] - 1]) return false;
        seen[s[i][col] - 1] = true;
    }
    return true;
}

bool isSquareValid(int s[9][9], int row, int col) {
    // Move to top left corner of the square.
    row = row / 3 * 3;
    col = col / 3 * 3;

    bool seen[9] = {false};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s[row + i][col + j] == 0) continue;
            if (seen[s[row + i][col + j] - 1]) return false;
            seen[s[row + i][col + j] - 1] = true;
        }
    }
    return true;
}

bool solve(int s[9][9]) {

    // Identify an empty position.
    int row, col;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (s[row][col] == 0) break;
        }
        if (col < 9 && s[row][col] == 0) break;
    }

    // No empty position, sudoku is solved.
    if (row == 9 && col == 9) return true;

    // Try to solve this position.
    for (int i = 1; i <= 9; i++) {
        s[row][col] = i;
        if (isRowValid(s, row) &&
            isColValid(s, col) &&
            isSquareValid(s, row, col) &&
            solve(s)) return true;
        s[row][col] = 0;
    }
    return false;
}

bool testIsRowValid() {
    int s[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {1, 2, 3, 4, 5, 6, 7, 8, 9},
                   {9, 8, 7, 6, 5, 4, 3, 2, 1},
                   {0, 2, 0, 4, 0, 6, 0, 8, 0},
                   {1, 0, 3, 0, 5, 0, 7, 0, 9},
                   {0, 0, 0, 0, 0, 6, 7, 8, 9},
                   {1, 2, 3, 4, 5, 0, 0, 0, 0},
                   {1, 1, 2, 3, 4, 5, 6, 7, 8},
                   {0, 1, 3, 4, 5, 5, 0, 6, 0}};

    return isRowValid(s, 0) && isRowValid(s, 1) && isRowValid(s, 2) &&
           isRowValid(s, 3) && isRowValid(s, 4) && isRowValid(s, 5) &&
           isRowValid(s, 6) && !isRowValid(s, 7) && !isRowValid(s, 8);
}

bool testIsColValid() {
    int s[9][9] = {{0, 1, 9, 0, 1, 0, 1, 1, 0},
                   {0, 2, 8, 2, 0, 0, 2, 1, 1},
                   {0, 3, 7, 0, 3, 0, 3, 2, 3},
                   {0, 4, 6, 4, 0, 0, 4, 3, 4},
                   {0, 5, 5, 0, 5, 0, 5, 4, 5},
                   {0, 6, 4, 6, 0, 6, 0, 5, 5},
                   {0, 7, 3, 0, 7, 7, 0, 6, 0},
                   {0, 8, 2, 8, 0, 8, 0, 7, 6},
                   {0, 9, 1, 0, 9, 9, 0, 8, 0}};

    return isColValid(s, 0) && isColValid(s, 1) && isColValid(s, 2) &&
           isColValid(s, 3) && isColValid(s, 4) && isColValid(s, 5) &&
           isColValid(s, 6) && !isColValid(s, 7) && !isColValid(s, 8);
}

bool testIsSquareValid() {
    int s[9][9] = {{0, 0, 0, 1, 2, 3, 9, 8, 7},
                   {0, 0, 0, 4, 5, 6, 6, 5, 4},
                   {0, 0, 0, 7, 8, 9, 3, 2, 1},
                   {0, 2, 0, 1, 0, 3, 0, 0, 0},
                   {4, 0, 6, 0, 5, 0, 4, 5, 6},
                   {0, 8, 0, 7, 0, 9, 7, 8, 9},
                   {1, 2, 2, 1, 0, 0, 0, 2, 3},
                   {4, 5, 6, 4, 5, 5, 0, 0, 6},
                   {7, 8, 9, 0, 0, 9, 7, 8, 8}};

    return isSquareValid(s, 0, 0) && isSquareValid(s, 0, 3) &&
           isSquareValid(s, 0, 6) && isSquareValid(s, 3, 0) &&
           isSquareValid(s, 3, 3) && isSquareValid(s, 3, 6) &&
           !isSquareValid(s, 6, 0) && !isSquareValid(s, 6, 3) &&
           !isSquareValid(s, 6, 6);
}

void print(int s[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << s[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool assert(int a[9][9], int b[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

bool testEasy() {
    int s[9][9] = {{0, 3, 0, 0, 4, 0, 0, 0, 0},
                   {0, 9, 5, 0, 2, 6, 3, 7, 4},
                   {4, 0, 7, 0, 0, 1, 6, 0, 2},
                   {2, 0, 0, 0, 5, 0, 0, 0, 0},
                   {0, 4, 0, 3, 0, 2, 0, 9, 0},
                   {0, 0, 0, 0, 8, 0, 0, 0, 3},
                   {5, 0, 4, 6, 0, 0, 1, 0, 7},
                   {3, 6, 1, 2, 7, 0, 8, 4, 0},
                   {0, 0, 0, 0, 1, 0, 0, 6, 0}};

    int r[9][9] = {{6, 3, 2, 5, 4, 7, 9, 1, 8},
                   {1, 9, 5, 8, 2, 6, 3, 7, 4},
                   {4, 8, 7, 9, 3, 1, 6, 5, 2},
                   {2, 1, 3, 7, 5, 9, 4, 8, 6},
                   {7, 4, 8, 3, 6, 2, 5, 9, 1},
                   {9, 5, 6, 1, 8, 4, 7, 2, 3},
                   {5, 2, 4, 6, 9, 8, 1, 3, 7},
                   {3, 6, 1, 2, 7, 5, 8, 4, 9},
                   {8, 7, 9, 4, 1, 3, 2, 6, 5}};

    return solve(s) && assert(s, r);
}

bool testMedium() {
    int s[9][9] = {{0, 0, 0, 0, 0, 0, 0, 2, 7},
                   {0, 0, 0, 0, 1, 2, 0, 0, 8},
                   {0, 3, 2, 0, 0, 6, 0, 0, 0},
                   {0, 8, 5, 4, 0, 0, 0, 0, 1},
                   {0, 0, 4, 0, 0, 0, 9, 0, 0},
                   {7, 0, 0, 0, 0, 5, 4, 8, 0},
                   {0, 0, 0, 9, 0, 0, 5, 7, 0},
                   {6, 0, 0, 2, 3, 0, 0, 0, 0},
                   {8, 9, 0, 0, 0, 0, 0, 0, 0}};

    int r[9][9] = {{1, 6, 8, 5, 4, 9, 3, 2, 7},
                   {5, 7, 9, 3, 1, 2, 6, 4, 8},
                   {4, 3, 2, 8, 7, 6, 1, 9, 5},
                   {9, 8, 5, 4, 2, 3, 7, 6, 1},
                   {3, 1, 4, 7, 6, 8, 9, 5, 2},
                   {7, 2, 6, 1, 9, 5, 4, 8, 3},
                   {2, 4, 3, 9, 8, 1, 5, 7, 6},
                   {6, 5, 7, 2, 3, 4, 8, 1, 9},
                   {8, 9, 1, 6, 5, 7, 2, 3, 4}};

    return solve(s) && assert(s, r);
}

bool testHard() {
    int s[9][9] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 3, 6, 0, 0, 0, 0, 0},
                   {0, 7, 0, 0, 9, 0, 2, 0, 0},
                   {0, 5, 0, 0, 0, 7, 0, 0, 0},
                   {0, 0, 0, 0, 4, 5, 7, 0, 0},
                   {0, 0, 0, 1, 0, 0, 0, 3, 0},
                   {0, 0, 1, 0, 0, 0, 0, 6, 8},
                   {0, 0, 8, 5, 0, 0, 0, 1, 0},
                   {0, 9, 0, 0, 0, 0, 4, 0, 0}};

    int r[9][9] = {{8, 1, 2, 7, 5, 3, 6, 4, 9},
                   {9, 4, 3, 6, 8, 2, 1, 7, 5},
                   {6, 7, 5, 4, 9, 1, 2, 8, 3},
                   {1, 5, 4, 2, 3, 7, 8, 9, 6},
                   {3, 6, 9, 8, 4, 5, 7, 2, 1},
                   {2, 8, 7, 1, 6, 9, 5, 3, 4},
                   {5, 2, 1, 9, 7, 4, 3, 6, 8},
                   {4, 3, 8, 5, 2, 6, 9, 1, 7},
                   {7, 9, 6, 3, 1, 8, 4, 5, 2}};

    return solve(s) && assert(s, r);
}

int main() {
    int counter = 0;
    if (!testIsRowValid()) {
        counter++;
        std::cout << "IsRowValid test failed!" << std::endl;
    }
    if (!testIsColValid()) {
        counter++;
        std::cout << "IsColValid test failed!" << std::endl;
    }
    if (!testIsSquareValid()) {
        counter++;
        std::cout << "IsSquareValid test failed!" << std::endl;
    }
    if (!testEasy()) {
        counter++;
        std::cout << "Easy sudoku test failed!" << std::endl;
    }
    if (!testMedium()) {
        counter++;
        std::cout << "Medium sudoku test failed!" << std::endl;
    }
    if (!testHard()) {
        counter++;
        std::cout << "Hard sudoku test failed!" << std::endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

