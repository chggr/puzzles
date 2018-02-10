#include <stdio.h>

// Task description: Given a screen that consists of black and white pixels,
// design an algorithm to find the maximum square in the screen so that all its
// four borders are filled with black pixels.
//
// E.g. for input:   {0, 0, 0, 0, 0,
//                    0, 1, 1, 1, 0,
//                    0, 1, 0, 1, 0,
//                    0, 1, 1, 1, 0,
//                    0, 0, 0, 0, 0};
//
//       the method should detect the square at pixel (1, 1) with side 3 pixels.
//
// Solution: The first implementation below is a brute force algorithm that
// initially sets the side equal to the maximum and progressively decreases it
// until a square has been found in the matrix. Since we are searching for
// progressively smaller squares, we know that the first square identified will
// be the biggest. If the screen is square with side N, the runtime complexity
// of this approach is O(N^4) and the space complexity is O(1).
//
// The second implementation improves the runtime complexity of the brute force
// solution by doing some pre-processing. A second array is created with similar
// dimensions and for each black pixel in the matrix we store the number of
// black pixels at its right and bottom. For white pixels in the matrix we
// simply store (0, 0). Using this new array, the complexity of is_square() is
// reduced from O(N) to just O(1). The runtime complexity of this solution is
// therefore O(N ^ 3), but the space complexity increases to O(N ^ 2).

struct Square {
    int row;
    int col;
    int side;
};

// Returns a square with the given position and side.
struct Square square(int row, int col, int side) {
    struct Square square;
    square.row = row;
    square.col = col;
    square.side = side;
    return square;
}

// Checks whether there is a valid square at the given position and with the
// given side. Checks each side in order: left, right, top, bottom.
int is_square_brute(int array[], int width, int height, int row, int col, int side) {
    if (row + side >= height) return 0;
    if (col + side >= width) return 0;

    for (int i = 0; i < side; i++) {
        if (array[(row + i) * width + col] != 1) return 0;
        if (array[(row + i) * width + col + side] != 1) return 0;
        if (array[row * width + col + i] != 1) return 0;
        if (array[(row + side) * width + col + i] != 1) return 0;
    }
    return 1;
}

struct Square search_brute(int array[], int width, int height) {
    int side = width < height ? width : height;

    while (side > 0) {
        for (int row = 0; row < side; row++) {
            for (int col = 0; col < side; col++) {
                if (is_square_brute(array, width, height, row, col, side)) {
                    return square(row, col, side);
                }
            }
        }
        side--;
    }
    return square(0, 0, 0);
}

// Holds the number of black pixels on the
// right and bottom of current pixel.
struct Blacks {
    int right;
    int bottom;
};

// Pre-processes the matrix and populates the blacks array.
void preprocess(int array[], struct Blacks blacks[], int width, int height) {
    for (int row = height - 1; row >= 0; row--) {
        for (int col = width - 1; col >= 0; col--) {
            int right = 0;
            int bottom = 0;

            // Only calculate for black cells.
            if (array[row * width + col] == 1) {
                if (col != width - 1) {
                    right = blacks[row * width + col + 1].right + 1;
                }
                if (row != height - 1) {
                    bottom = blacks[(row + 1) * width + col].bottom + 1;
                }
            }

            blacks[row * width + col].right = right;
            blacks[row * width + col].bottom = bottom;
        }
    }
}

// Checks whether there is a valid square at the given position and with the
// given side. Checks each side in order: top, left, bottom, right.
int is_square(int array[], struct Blacks blacks[], int width, int height,
              int row, int col, int side) {
    if (row + side >= height) return 0;
    if (col + side >= width) return 0;

    if (blacks[row * width + col].right -
        blacks[row * width + col + side].right < side) return 0;

    if (blacks[row * width + col].bottom -
        blacks[(row + side) * width + col].bottom < side) return 0;

    if (blacks[(row + side) * width + col].right -
        blacks[(row + side) * width + col + side].right < side) return 0;

    if (blacks[row * width + col + side].bottom -
        blacks[(row + side) * width + col + side].bottom < side) return 0;
    return 1;
}

struct Square search(int array[], int width, int height) {
    struct Blacks blacks[width * height];
    preprocess(array, blacks, width, height);

    int side = width < height ? width : height;
    while (side > 0) {
        for (int row = 0; row < side; row++) {
            for (int col = 0; col < side; col++) {
                if (is_square(array, blacks, width, height, row, col, side)) {
                    return square(row, col, side);
                }
            }
        }
        side--;
    }
    return square(0, 0, 0);
}

int test_all_white() {
    int array[] = {0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0};

    struct Square brute = search_brute(array, 5, 5);
    struct Square better = search(array, 5, 5);
    return brute.row == 0 && brute.col == 0 && brute.side == 0 &&
           better.row == 0 && better.col == 0 && better.side == 0;
}

int test_no_square() {
    int array[] = {0, 0, 0, 0, 0,
                   0, 1, 1, 1, 0,
                   0, 0, 0, 1, 0,
                   0, 1, 1, 1, 0,
                   0, 0, 0, 0, 0};

    struct Square brute = search_brute(array, 5, 5);
    struct Square better = search(array, 5, 5);
    return brute.row == 0 && brute.col == 0 && brute.side == 0 &&
           better.row == 0 && better.col == 0 && better.side == 0;
}

int test_one_square() {
    int array[] = {0, 0, 0, 0, 0,
                   0, 1, 1, 1, 0,
                   0, 1, 0, 1, 0,
                   0, 1, 1, 1, 0,
                   0, 0, 0, 0, 0};

    struct Square brute = search_brute(array, 5, 5);
    struct Square better = search(array, 5, 5);
    return brute.row == 1 && brute.col == 1 && brute.side == 2 &&
           better.row == 1 && better.col == 1 && better.side == 2;
}

int test_two_squares() {
    int array[] = {0, 0, 0, 0, 0,
                   0, 1, 1, 1, 1,
                   0, 1, 1, 1, 1,
                   0, 1, 1, 1, 1,
                   0, 1, 1, 1, 1};

    struct Square brute = search_brute(array, 5, 5);
    struct Square better = search(array, 5, 5);
    return brute.row == 1 && brute.col == 1 && brute.side == 3 &&
           better.row == 1 && better.col == 1 && better.side == 3;
}

int test_all_black() {
    int array[] = {1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1};

    struct Square brute = search_brute(array, 5, 5);
    struct Square better = search(array, 5, 5);
    return brute.row == 0 && brute.col == 0 && brute.side == 4 &&
           better.row == 0 && better.col == 0 && better.side == 4;
}

int main() {
    int counter = 0;
    if (!test_all_white()) {
        printf("All white pixels test failed!\n");
        counter++;
    }
    if (!test_no_square()) {
        printf("No square test failed!\n");
        counter++;
    }
    if (!test_one_square()) {
        printf("One square test failed!\n");
        counter++;
    }
    if (!test_two_squares()) {
        printf("Two squares test failed!\n");
        counter++;
    }
    if (!test_all_black()) {
        printf("All black pixels test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

