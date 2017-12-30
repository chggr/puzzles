#include <stdio.h>

// Task description: A map is represented as a two dimensional integer array,
// with the value at each location indicating the height above sea level.A value
// equal to zero indicates water. Write a method that will read such a map and
// return the maximum continuous water surface area. Continuous water surface
// consists of positions with zero value that are connected vertically,
// horizontally or diagonally.
//
// E.g. for the following 5x5 map, the answer is 6.
//
//    int map[5][5] = {{0, 0, 1, 1, 0},
//                     {0, 0, 1, 0, 0},
//                     {1, 2, 2, 0, 0},
//                     {0, 0, 1, 0, 1},
//                     {0, 1, 2, 1, 1}};
//
// Solution: The implementation below uses a modified depth first algorithm to
// calculate the surface area of each water pond in the given map and then pick
// up the maximum. It iterates through the entire map and invokes depth first
// search whenever a water cell with zero value is encountered. This calculates
// the surface area for the current pond, which is then compared with the
// maximum area seen so far.
//
// The calculate() method is invoked recursively in a depth first manner to
// calculate the surface area of a given pond. The algorithm first sets the
// value of the current position to -1 to avoid double counting and then looks
// at nearby positions to check whether they are also water cells. The input
// array is modified as part of this process. This can be avoided by allocating
// a new array just to hold the positions that have already been visited.
//
// The runtime complexity of this implementation is O(W*L) where W is the width
// and L is the length of the map.

// Calculates the water surface size that starts at the given row and col.
int calculate(int len, int wid, int map[len][wid], int row, int col) {
    if (row < 0 || row >= len ||
        col < 0 || col >= wid ||
        map[row][col] != 0) return 0;

    map[row][col] = -1;
    int size = 1;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            size += calculate(len, wid, map, row + i, col + j);
        }
    }
    return size;
}

// Identifies the maximum water surface on the given map.
int max_water_surface(int len, int wid, int map[len][wid]) {
    int max = 0;
    int current = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < wid; j++) {
            if (map[i][j] == 0) {
                current = calculate(len, wid, map, i, j);
                if (current > max) max = current;
            }
        }
    }
    return max;
}

int test_all_water() {
    int map[5][5] = {{0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0}};

    return 25 == max_water_surface(5, 5, map);
}

int test_all_land() {
    int map[5][5] = {{1, 2, 2, 1, 1},
                     {2, 3, 3, 2, 1},
                     {2, 3, 4, 3, 2},
                     {1, 2, 3, 2, 1},
                     {1, 1, 2, 1, 1}};

    return 0 == max_water_surface(5, 5, map);
}

int test_water_land() {
    int map[5][5] = {{0, 0, 1, 1, 0},
                     {0, 0, 1, 0, 0},
                     {1, 2, 2, 0, 0},
                     {0, 0, 1, 0, 1},
                     {0, 1, 2, 1, 1}};

    return 6 == max_water_surface(5, 5, map);
}

int main() {
    int counter = 0;
    if (!test_all_water()) {
        printf("All water test failed!\n");
        counter++;
    }
    if (!test_all_land()) {
        printf("All land test failed!\n");
        counter++;
    }
    if (!test_water_land()) {
        printf("Water land test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

