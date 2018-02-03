#include <stdio.h>

// Task description: Given an array of positive integers, write a method to
// return the length of the shortest sub-array whose sum is at least equal to
// a given target.
//
// E.g. for input array {5, 2, 3, 1, 4} and target 7 the method should return 2
//
// Solution: The first implementation below uses a brute force approach: it
// iterates through all elements of the array, treating each element as the
// start of the sub-array in question. It then calculates the sub-array length
// by looping through the remaining elements, calculating the running sum and
// capturing the length when the running sum is equal or greater to the target.
// The space complexity of this implementation is O(1) and the runtime
// complexity is O(n^2), because for each element we iterate through possibly
// all the remaining elements in the array until the target is reached.
//
// The second implementation is more efficient, because it iterates through the
// array only once. It uses a sliding window that gets bigger while the running
// sum is less than the target and smaller while the running sum is larger than
// the target. The length of the smallest window that satisfies the requirement
// is finally returned. The space complexity of this approach is O(1) and the
// runtime complexity is O(n), since we iterate through the array only once.

int get_length_brute(int array[], int size, int target) {
    if (size == 0) return 0;

    int length = 0;
    int sum = 0;
    int sub_length = 0;

    for (int i = 0; i < size; i++) {
        sum = 0;
        sub_length = 0;
        for (int j = i; j < size; j++) {
            sum += array[j];
            sub_length++;
            if (sum >= target) {
                if (length == 0 || sub_length < length) {
                   length = sub_length;
                }
                break;
            }
        }
        if (length == 1) break;
    }
    return length;
}

int get_length(int array[], int size, int target) {
    if (size == 0) return 0;

    int min_len = 0;
    int wind_len = 1;
    int wind_sum = array[0];
    int idx = 0;

    while (1) {
        // If target has been reached, check the window length
        // against the minimum length and decrease the window
        // for the next iteration. Otherwise increase the window.
        if (wind_sum >= target) {
            if (min_len == 0 || wind_len < min_len) {
                min_len = wind_len;
            }
            wind_sum -= array[idx - wind_len + 1];
            wind_len--;
        } else {
            idx++;
            if (idx >= size) break;
            wind_sum += array[idx];
            wind_len++;
        }
    }
    return min_len;
}

int test_array_empty() {
    return 0 == get_length_brute(NULL, 0, 10) &&
           0 == get_length(NULL, 0, 10);
}

int test_target_large() {
    int array[] = {5, 2, 3, 1, 4};
    return 0 == get_length_brute(array, 5, 30) &&
           0 == get_length(array, 5, 30);
}

int test_target_small() {
    int array_start[] = {5, 2, 3, 1, 4};
    int array_end[] = {4, 2, 3, 1, 5};
    return 1 == get_length_brute(array_start, 5, 5) &&
           1 == get_length_brute(array_end, 5, 5) &&
           1 == get_length(array_start, 5, 5) &&
           1 == get_length(array_end, 5, 5);
}

int test_target_exact() {
    int array[] = {5, 2, 3, 1, 4};
    return 5 == get_length_brute(array, 5, 15) &&
           5 == get_length(array, 5, 15);
}

int test_target_medium() {
    int array_start[] = {5, 2, 3, 1, 4};
    int array_end[] = {2, 3, 1, 4, 5};
    return 2 == get_length_brute(array_start, 5, 7) &&
           2 == get_length_brute(array_end, 5, 7) &&
           2 == get_length(array_start, 5, 7) &&
           2 == get_length(array_end, 5, 7);
}

int main() {
    int counter = 0;
    if (!test_array_empty()) {
        printf("Empty array test failed!\n");
        counter++;
    }
    if (!test_target_large()) {
        printf("Large target test failed!\n");
        counter++;
    }
    if (!test_target_small()) {
        printf("Small target test failed!\n");
        counter++;
    }
    if (!test_target_exact()) {
        printf("Exact target test failed!\n");
        counter++;
    }
    if (!test_target_medium()) {
        printf("Medium target test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

