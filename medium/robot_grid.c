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
// again. The improved runtime complexity is O(XY), as each position is now
// evaluated only once.

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

int test_no_blocks() {
    int grid[] = {1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1};
    int mem[25] = { 0 };
    return 1 == move(5, 5, grid, 0, 0) &&
           1 == move_mem(5, 5, grid, mem, 0, 0);
}

int test_fully_blocked() {
    int grid[] = {1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1,
                  1, 0, 1, 1, 1};
    int mem[25] = { 0 };
    printf("%d", move_mem(5, 5, grid, mem, 0, 0));
    return 0 == move(5, 5, grid, 0, 0) &&
           0 == move_mem(5, 5, grid, mem, 0, 0);
}

int test_partially_blocked() {
    int grid[] = {1, 1, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 0, 1,
                  1, 0, 1, 1, 1};
    int mem[25] = { 0 };
    return 1 == move(5, 5, grid, 0, 0) &&
           1 == move_mem(5, 5, grid, mem, 0, 0);
}

int test_destination_blocked() {
    int grid[] = {1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 0};
    int mem[25] = { 0 };
    return 0 == move(5, 5, grid, 0, 0) &&
           0 == move_mem(5, 5, grid, mem, 0, 0);
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

