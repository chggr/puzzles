#include <stdio.h>

// Task description: There is a grid with r rows and c columns and a robot is
// placed on its upper left corner. The robot can only move in two directions,
// either right or down, but certain cells on the grid are blocked so that the
// robot cannot step on them. Write a method to check whether there is at least
// one path in the grid that the robot can follow in order to move from the
// starting position to the bottom right corner.
//
// Solution: The implementation below is recursive, starts from index (0,0) and
// attempts to move right or down in each step until we have either reached the
// bottom right corner of the grid or until we are terminally blocked. The
// method returns true in the former case and false in the latter. The runtime
// complexity of this approach is O(2^(r+c)) because each path has r + c steps
// and there are two choices that we can make at each step (right or bottom).
//
// The second implementation below uses memoization to improve the runtime
// performance significantly. When a position in the grid is first visited and
// evaluated, the result is stored in a secondary matrix so that the recursive
// algorithm does not need to re-evaluate the same position when it visits it
// again. The improved runtime complexity is O(r * c), as each position is now
// evaluated only once.
//
// Finally, the third implementation uses an iterative dynamic programming
// approach to avoid recursive calls and further reduce space complexity to O(1)
// while retaining runtime complexity of O(r * c). Both previous implementations
// were top-down, whereas this one is bottom up. It iterates through the grid
// from bottom right to top left and at each position calculates the number of
// steps required to reach the destination. This can be computed as the minimum
// value of the two cells at right and down. Finally the origin will contain the
// minimum number of steps to reach the destination.

int move(int r, int c, int *grid, int x, int y) {
    if (x >= c || y >= r || !grid[y * c + x]) return 0;
    if (x == (c - 1) && y == (r - 1)) return 1;
    return move(r, c, grid, x + 1, y) ||
           move(r, c, grid, x, y + 1);
}

int move_mem(int r, int c, int *grid, int *mem, int x, int y) {
    if (x >= c || y >= r || !grid[y * c + x]) return 0;
    if (x == (c - 1) && y == (r - 1)) return 1;

    if (!mem[y * c + x + 1]) {
        if (move_mem(r, c, grid, mem, x + 1, y)) return 1;
        mem[y * c + x + 1] = 1;
    }

    if (!mem[(y + 1) * c + x]) {
        if (move_mem(r, c, grid, mem, x, y + 1)) return 1;
        mem[(y + 1) * c + x] == 1;
    }
    return 0;
}

int move_dyn(int r, int c, int *grid) {

    for (int row = r - 1; row >= 0; row--) {
        for (int col = c - 1; col >= 0; col--) {

            // Do not calculate at blocks or at the destination.
            if (grid[row * c + col] == 0) continue;
            if (row == r - 1 && col == c - 1) continue;

            int down = row < r - 1 ? grid[(row + 1) * c + col] : 0;
            int right = col < c - 1 ? grid[row * c + col + 1] : 0;

            // No path to destination.
            if (down == 0 && right == 0) {
                grid[row * c + col] = 0;
                continue;
            }

            if (down > 0 && right > 0) {
                grid[row * c + col] = down < right ? down : right;
            } else if (down > 0) {
                grid[row * c + col] = down;
            } else {
                grid[row * c + col] = right;
            }
            grid[row * c + col]++;
        }
    }

    // If there is a valid path to the destination, grid[0] will
    // contain the minimum number of steps to reach the destination.
    return grid[0] > 0;
}

int test_no_blocks() {
    int grid[] = {1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1};
    int mem[25] = { 0 };
    return 1 == move(5, 5, grid, 0, 0) &&
           1 == move_mem(5, 5, grid, mem, 0, 0) &&
           1 == move_dyn(5, 5, grid);
}

int test_fully_blocked() {
    int grid[] = {1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1};
    int mem[25] = { 0 };
    return 0 == move(5, 5, grid, 0, 0) &&
           0 == move_mem(5, 5, grid, mem, 0, 0) &&
           0 == move_dyn(5, 5, grid);
}

int test_partially_blocked() {
    int grid[] = {1, 1, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 1, 1};
    int mem[25] = { 0 };
    return 1 == move(5, 5, grid, 0, 0) &&
           1 == move_mem(5, 5, grid, mem, 0, 0) &&
           1 == move_dyn(5, 5, grid);
}

int test_destination_blocked() {
    int grid[] = {1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 0};
    int mem[25] = { 0 };
    return 0 == move(5, 5, grid, 0, 0) &&
           0 == move_mem(5, 5, grid, mem, 0, 0) &&
           0 == move_dyn(5, 5, grid);
}

int main() {
    int counter = 0;
    if (!test_no_blocks()) {
        printf("No blocks test failed!\n");
        counter++;
    }
    if (!test_fully_blocked()) {
        printf("Fully blocked test failed!\n");
        counter++;
    }
    if (!test_partially_blocked()) {
        printf("Partially blocked test failed!\n");
        counter++;
    }
    if (!test_destination_blocked()) {
        printf("Destination blocked test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

