#include <stdio.h>

// Task description: Given an NxN integer matrix, write a method to calculate
// and return the sub-matrix with the largest possible sum.
//
// Solution: The first implementation below is a brute force solution that
// iterates through all possible sub-arrays, computing the area of each one and
// updating the maximum area encountered so far. The space complexity of this
// approach is O(1), but the runtime complexity is O(N^6). We go through each
// element of the array, using it as the top left corner of the sub-array. Then
// we calculate all possible sub-arrays starting from that position and for each
// one compute the area. Therefore we need O(N^2) to go through all elements,
// O(N^2) to calculate all sub-arrays for each and another O(N^2) to compute the
// area for each sub-array. The total is O(N^6).
//
// The second implementation is similar to the first one but tries to optimize
// the way the sum of a sub-array is calculated. The time to compute the sum can
// be reduced from O(N^2) to O(1) if we pre-compute for each element the area of
// the sub-array starting at (0,0) and ending at that position. For example, if
// we need to calculate the sum of sub-array A below we can do this in O(1) as
// shown below. The runtime complexity of this approach is O(N^4) and the space
// complexity is O(N^2).
//
//     A = sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1).
//       = (A + B + C + D) - (B + D) - (C + D) + D
//
//     0_______x1______x2____
//     |       |       |     |
//     |   D   |   B   |     |
//   y1|_______|_______|     |
//     |       |       |     |
//     |   C   |   A   |     |
//   y2|_______|_______|     |
//     |                     |
//     |                     |
//     |_____________________|
//
// The third implementation is the most optimal, with runtime complexity of
// O(N^3) and space complexity O(N). In more detail, if R is the number of rows
// and C is the number of columns, the runtime complexity of this algorithm is
// O(R^2 * C) and the space complexity O(C). It leverages a well known algorithm
// that retrieves the maximum sum of a one dimensional sub-array in O(N). Every
// sub-array can be represented as a contiguous sequence of rows and columns. If
// we iterate through every contiguous sequence of rows, we would then just need
// to find for each of those the set of columns that gives the highest sum. A
// double for loop is used to go through all contiguous sequences of rows. For
// each one we calculate the sum of columns and use the aforementioned algorithm
// to find the maximum sum.

// Calculates the sum of all elements in a sub-array.
int sub_sum_brute(int array[], int width, int height,
                  int from_row, int from_col , int to_row, int to_col) {

    int sum = 0;
    for (int row = from_row; row <= to_row; row++) {
        for (int col = from_col; col <= to_col; col++) {
            if (row >= 0 && col >= 0 && row < height && col < width) { 
                sum += array[row * width + col];
            }
        }
    }
    return sum;
}

// Calculates the sub-array with the largest sum in the given array.
int max_subarray_brute(int array[], int width, int height) {
    int max = 0;
    int current = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            for (int r = row + 1; r < height; r++) {
                for (int c = col + 1; c < width; c++) {
                    current = sub_sum_brute(array, width, height, row, col, r, c);
                    if (current > max) max = current;
                }
            }
        }
    }
    return max;
}

// Populates each position in areas with the area of the sub-array
// starting at (0,0) and ending at that position.
void preprocess(int array[], int areas[], int width, int height) {
    int current = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            current = 0;
            if (row > 0) {
                current += areas[(row - 1) * width + col];
            }
            if (col > 0) {
                current += areas[row * width + col - 1];
            }
            if (row > 0 && col > 0) {
                current -= areas[(row - 1) *  width + col - 1];
            }
            current += array[row * width + col];
            areas[row * width + col] = current;
        }
    }
}

// Calculates the sum of all elements in a sub-array.
int sub_sum_better(int array[], int areas[], int width, int height,
                   int from_row, int from_col, int to_row, int to_col) {

    from_col = from_col < 0 ? 0 : from_col;
    from_row = from_row < 0 ? 0 : from_row;

    to_col = to_col >= width ? width - 1 : to_col;
    to_row = to_row >= height ? height - 1 : to_row;

    int result = areas[to_row * width + to_col];
    if (from_col > 0) {
        result -= areas[to_row * width + from_col - 1];
    }
    if (from_row > 0) {
        result -= areas[(from_row - 1) * width + to_col];
    }
    if (from_row > 0 && from_col > 0) {
        result += areas[(from_row - 1) * width + from_col - 1];
    }
    return result;
}

// Calculates the sub-array with the largest sum in the given array.
int max_subarray_better(int array[], int width, int height) {
    int areas[width * height];
    preprocess(array, areas, width, height);

    int max = 0;
    int current = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            for (int r = row + 1; r < height; r++) {
                for (int c = col + 1; c < width; c++) {
                    current = sub_sum_better(array, areas, width,
                                             height, row, col, r, c);
                    if (current > max) max = current;
                }
            }
        }
    }
    return max;
}

// Returns the sum of the maximum sub-array in the given array.
int max_subarray(int array[], int size) {
    int max = 0;
    int current = 0;
    for (int i = 0; i < size; i++) {
        current += array[i];
        if (current > max) max = current;
        if (current <= 0) current = 0;
    }
    return max;
}

// Calculates the sub-array with the largest sum in the given array.
int max_subarray_optimal(int array[], int width, int height) {
    int max = 0;
    int current = 0;

    for (int row = 0; row < height; row++) {
        int column_sums[width];
        for (int i = 0; i < width; i++) {
            column_sums[i] = 0;
        }

        for (int r = row; r < height; r++) {
            for (int c = 0; c < width; c++) {
                column_sums[c] += array[r * width + c];
            }

            current = max_subarray(column_sums, width);
            if (current > max) max = current;
        }
    }
    return max;
}

int zeros[] = {0, 0, 0, 0, 0,
               0, 0, 0, 0, 0,
               0, 0, 0, 0, 0,
               0, 0, 0, 0, 0,
               0, 0, 0, 0, 0};

int ones[] = {1, 1, 1, 1, 1,
              1, 1, 1, 1, 1,
              1, 1, 1, 1, 1,
              1, 1, 1, 1, 1,
              1, 1, 1, 1, 1};

int are_equal(int a[], int b[], int length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int test_sub_sum_brute() {
    return 0 == sub_sum_brute(zeros, 5, 5, 0, 0, 0, 0) &&
           0 == sub_sum_brute(zeros, 5, 5, 0, 0, 4, 4) &&
           1 == sub_sum_brute(ones, 5, 5, 0, 0, 0, 0) &&
           4 == sub_sum_brute(ones, 5, 5, 0, 0, 1, 1) &&
           9 == sub_sum_brute(ones, 5, 5, 0, 0, 2, 2) &&
           16 == sub_sum_brute(ones, 5, 5, 0, 0, 3, 3) &&
           25 == sub_sum_brute(ones, 5, 5, 0, 0, 4, 4) &&
           9 == sub_sum_brute(ones, 5, 5, 2, 2, 7, 7) &&
           25 == sub_sum_brute(ones, 5, 5, -1, -1, 7, 7) &&
           0 == sub_sum_brute(ones, 5, 5, 1, 1, 0, 0);
}

int test_preprocess() {
    int expected[] = {1,  2,  3,  4,  5,
                      2,  4,  6,  8, 10,
                      3,  6,  9, 12, 15,
                      4,  8, 12, 16, 20,
                      5, 10, 15, 20, 25};

    int result_zeros[25];
    preprocess(zeros, result_zeros, 5, 5);

    int result_ones[25];
    preprocess(ones, result_ones, 5, 5);

    return are_equal(zeros, result_zeros, 25) &&
           are_equal(expected, result_ones, 25);
}

int test_sub_sum_better() {
    int areas_zeros[25];
    preprocess(zeros, areas_zeros, 5, 5);

    int areas_ones[25];
    preprocess(ones, areas_ones, 5, 5);

    return 0 == sub_sum_better(zeros, areas_zeros, 5, 5, 0, 0, 0, 0) &&
           0 == sub_sum_better(zeros, areas_zeros, 5, 5, 0, 0, 4, 4) &&
           1 == sub_sum_better(ones, areas_ones, 5, 5, 0, 0, 0, 0) &&
           4 == sub_sum_better(ones, areas_ones, 5, 5, 0, 0, 1, 1) &&
           9 == sub_sum_better(ones, areas_ones, 5, 5, 0, 0, 2, 2) &&
           16 == sub_sum_better(ones, areas_ones, 5, 5, 0, 0, 3, 3) &&
           25 == sub_sum_better(ones, areas_ones, 5, 5, 0, 0, 4, 4) &&
           9 == sub_sum_better(ones, areas_ones, 5, 5, 2, 2, 7, 7) &&
           25 == sub_sum_better(ones, areas_ones, 5, 5, -1, -1, 7, 7) &&
           0 == sub_sum_better(ones, areas_ones, 5, 5, 1, 1, 0, 0);
}

int test_max_subarray() {
    int array[] = {1, 2, -4, 3, 1, -2, -1};
    return 4 == max_subarray(array, 7);
}

int test_all_zero() {
    return 0 == max_subarray_brute(zeros, 5, 5) &&
           0 == max_subarray_better(zeros, 5, 5) &&
           0 == max_subarray_optimal(zeros, 5, 5);
}

int test_all_one() {
    return 25 == max_subarray_brute(ones, 5, 5) &&
           25 == max_subarray_better(ones, 5, 5) &&
           25 == max_subarray_optimal(ones, 5, 5);
}

int test_negative() {
    int array[] = {-10,  9, 15, 12, -11,
                     4, -2,  6, -7,  12,
                   -17,  3, 21, 12, -18,
                    16,  5, 13, -9, -11,
                   -12, 17,  5, 12, -25};

    return 112 == max_subarray_brute(array, 5, 5) &&
           112 == max_subarray_better(array, 5, 5) &&
           112 == max_subarray_optimal(array, 5, 5);
}

int main() {
    int counter = 0;
    if (!test_sub_sum_brute()) {
        printf("Sub-array sum brute test failed!\n");
        counter++;
    }
    if (!test_preprocess()) {
        printf("Pre-process test failed!\n");
        counter++;
    }
    if (!test_sub_sum_better()) {
        printf("Sub-array sum better test failed!\n");
        counter++;
    }
    if (!test_max_subarray()) {
        printf("Max sub-array test failed!\n");
        counter++;
    }
    if (!test_all_zero()) {
        printf("All zero test failed!\n");
        counter++;
    }
    if (!test_all_one()) {
        printf("All one test failed!\n");
        counter++;
    }
    if (!test_negative()) {
        printf("Negative test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

