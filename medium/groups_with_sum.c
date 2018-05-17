#include <stdio.h>

// Task description: Given an array of N integers, write a method to calculate
// how many groups of two or three elements we can form so that the sum of all
// elements in that group is multiple of three.
//
// E.g. For input array {3, 6, 7, 2, 9}
//      the method should return 8
//      groups of two: {3,6}, {3,9}, {9,6}, {7,2}, {3,6,9}
//      groups of three: {3,7,2}, {7,2,6}, {7,2,9}
//
// Solution: The implementation below first creates an array of size 3 to store
// the count of numbers whose remainder is 0, 1, or 2. It then calculates the
// number of groups of two or three elements whose sum is multiple of 3 using
// the logic below:
//
// To find the number of groups of 2, we have the following possibilities:
// (a) Both elements have remainder zero
// (b) One element has remainder one and the other has remainder two
//
// To find the number of groups of 3, we have the following possibilities:
// (a) All three elements have remainder zero
// (b) All three elements have remainder one
// (c) All three elements have remainder two
// (d) One element has remainder one, the other two and the third three.
//
// The final result is obtained by calculating the different combinations using
// the n choose k formulas below and summing up the result.
//
// n choose 2 = n! / (2! * (n - 2)!)
//            = n * (n - 1) * (n- - 2)! / (2 * (n - 2)!)
//            = n * (n - 1) / 2
//
// n choose 3 = n! / (3! * (n - 3)!)
//            = n * (n - 1) * (n - 2) * (n - 3)! / (6 * (n - 3)!)
//            = n * (n - 1) * (n - 2) / 6

int count(int array[], int size) {
    if (size <= 1) return 0;

    int rem[3] = {0};
    for (int i = 0; i < size; i++) {
        rem[array[i] % 3]++;
    }

    int result = 0;

    // Count groups of two
    result += rem[0] * (rem[0] - 1) / 2;
    result += rem[1] * rem[2];

    // Count groups of three
    result += rem[0] * (rem[0] - 1) * (rem[0] - 2) / 6;
    result += rem[1] * (rem[1] - 1) * (rem[1] - 2) / 6;
    result += rem[2] * (rem[2] - 1) * (rem[2] - 2) / 6;
    result += rem[0] * rem[1] * rem[2];

    return result;
}

int test_small_array() {
    int array[] = {1};
    return 0 == count(NULL, 0) &&
           0 == count(array, 1);
}

int test_zero_groups() {
    int array[] = {7, 1};
    return 0 == count(array, 2);
}

int test_many_groups() {
    int array[] = {3, 6, 7, 2, 9};
    return 8 == count(array, 5);
}

int main() {
    int counter = 0;
    if (!test_small_array()) {
        counter++;
        printf("Small array test failed!\n");
    }
    if (!test_zero_groups()) {
        counter++;
        printf("Zero groups test failed!\n");
    }
    if (!test_many_groups()) {
        counter++;
        printf("Many groups test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

