#include <stdio.h>

// Task description: Given an array of positive integers that represent ground
// elevation, calculate how many snowflakes will be captured in the event of
// snow.
//
// e.g. for input array: {0, 2, 5, 3, 7, 2, 4, 8, 3, 1}
//      the method should return: 10
//
//                                            _____
//                          _____            |     |
//                         |     |  *     *  |     |
//              _____      |     |  *     *  |     |
//             |     |  *  |     |  *   __*__|     |
//             |     |__*__|     |  *  |           |_____
//        _____|                 |__*__|                 |
//       |                                               |_____
//  _____|                                                     |
//    0     2     5     3     7     2     4     8     3     1
//
// Solution: The first implementation below uses a brute force approach to
// calculate the number of snowflakes. It goes through all elements in the
// given array and for each element calculates the maximum value of the sub-
// array on the left and the maximum value of the sub-array on the right. The
// number of snowflakes at the current position will be equal to the minimum
// of those two values minus the current element. The space complexity of this
// approach is O(1), but the runtime complexity is O(n^2).
//
// The second implementation trades off memory to gain on runtime. It initially
// goes through the array from left to right once and uses an auxiliary array to
// store the maximum element at the left of each position. It subsequently goes
// through the array a second time from right to left. At each position, it
// calculates the maximum element on the right, compares it with the maximum
// element on the left from the auxiliary array and increments the count as
// necessary. The runtime complexity of this approach is O(n), as we only need
// to iterate through the elements of the given array only twice. The space
// complexity is also O(n) because of the auxiliary array.

int max_left(int array[], int size, int pos) {
    int max = 0;
    for (int i = pos - 1; i >= 0; i--) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

int max_right(int array[], int size, int pos) {
    int max = 0;
    for (int i = pos + 1; i < size; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

int snowflakes_brute(int array[], int size) {
    int max_l = 0;
    int max_r = 0;
    int min = 0;
    int count = 0;
    int result = 0;

    for (int i = 0; i < size; i++) {
        max_l = max_left(array, size, i);
        max_r = max_right(array, size, i);
        min = max_l < max_r ? max_l : max_r;
        count = min - array[i];
        if (count > 0) result += count;
    }
    return result;
}

int snowflakes(int array[], int size) {
    int max_left[size];
    max_left[0] = 0;
    int max_l = 0;
    for (int i = 1; i < size; i++) {
        if (array[i - 1] > max_l) max_l = array[i - 1];
        max_left[i] = max_l;
    }

    int min = 0;
    int max_r = 0;
    int count = 0;
    int result = 0;
    for (int i = size - 2; i >= 0; i--) {
        if (array[i + 1] > max_r) max_r = array[i + 1];
        min = max_left[i] < max_r ? max_left[i] : max_r;
        count = min - array[i];
        if (count > 0) result += count;
    }
    return result;
}

int test_level_ground() {
    int low[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int high[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    return 0 == snowflakes_brute(low, 10) &&
           0 == snowflakes_brute(high, 10) &&
           0 == snowflakes(low, 10) &&
           0 == snowflakes(high, 10);
}
int test_terrain() {
    int array[] = {0, 2, 5, 3, 7, 2, 4, 8, 3, 1};
    return 10 == snowflakes_brute(array, 10) &&
           10 == snowflakes(array, 10);
}

int test_mountain() {
    int array[] = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1};
    return 0 == snowflakes_brute(array, 10) &&
           0 == snowflakes(array, 10);
}

int test_valley() {
    int array[] = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4};
    return 16 == snowflakes_brute(array, 10) &&
           16 == snowflakes(array, 10);
}

int main() {
    int counter = 0;
    if (!test_level_ground()) {
        printf("Level ground test failed!\n");
        counter++;
    }
    if (!test_terrain()) {
        printf("Terrain test failed!\n");
        counter++;
    }
    if (!test_mountain()) {
        printf("Mountain test failed!\n");
        counter++;
    }
    if (!test_valley()) {
        printf("Valley test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

