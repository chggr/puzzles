#include <stdio.h>

// Task description: Given an array of positive and negative integers, find the
// continuous sequence with the largest sum and return the sum. Can your
// algorithm be improved?
//
// E.g. for sequence {2, -8, 3, -2, 4, -10} the sum is 5 for sequence {3, -2, 4}
//
// Solution: In the first implementation below we use a brute force approach to
// find the maximum sum of any continuous sequence. We go through all possible
// sequences in the input array, calculate each sum and keep track of the max.
// This approach is easy to implement but its runtime complexity is O(N^2) where
// N is the length of the array.
//
// The second implementation is much faster, since it goes through the input
// array just once. We need to use two variables, one to hold the maximum sum
// encountered so far and another to hold the running sum. In every step of the
// iteration, the current element is added to the running sum. If the running
// sum is greater than the max sum, the latter's value changes to the former's.
// On the contrary, if the running sum is less than zero, it is discarded. This
// is because it will never be part of the final sequence since its contribution
// to the sum is negative. The runtime complexity of this approach is O(N) where
// N is the length of the input array.
//
// Please note that both implementations return zero if the array only contains
// negative elements. In such cases we assume that the continuous sequence with
// the largest sum is the empty sequence with sum zero.

int max_sum_brute(int n[], int size) {
    int max_sum = 0;
    for (int i = 0; i < size; i++) {
        int sum = 0;
        for (int j = i; j < size; j++) {
            sum += n[j];
            if (sum > max_sum) max_sum = sum;
        }
    }
    return max_sum;
}

int max_sum(int n[], int size) {
    int sum = 0;
    int max_sum = 0;

    for (int i = 0; i < size; i++) {
        sum += n[i];
        if (sum > max_sum) max_sum = sum;
        if (sum < 0) sum = 0;
    }
    return max_sum;
}

int test_empty() {
    return 0 == max_sum_brute(0, 0) &&
           0 == max_sum(0, 0);
}

int test_single_positive() {
    int input[] = {5};
    return 5 == max_sum_brute(input, 1) &&
           5 == max_sum(input, 1);
}

int test_single_negative() {
    int input[] = {-5};
    return 0 == max_sum_brute(input, 1) &&
           0 == max_sum(input, 1);
}

int test_all_positives() {
    int input[] = {8, 4, 1, 9, 4, 5, 3};
    return 34 == max_sum_brute(input, 7) &&
           34 == max_sum(input, 7);;
}

int test_all_negatives() {
    int input[] = {-8, -4, -1, -9, -4, -5, -3};
    return 0 == max_sum_brute(input, 7) &&
           0 == max_sum(input, 7);
}

int test_mixed() {
    int input[] = {3, -8, -1, 2, 4, -2, 3};
    return 7 == max_sum_brute(input, 7) &&
           7 == max_sum(input, 7);
}

int main() {
    int counter = 0;
    if (!test_empty()) {
        printf("Empty array test failed!\n");
        counter++;
    }
    if (!test_single_positive()) {
        printf("Single positive test failed!\n");
        counter++;
    }
    if (!test_single_negative()) {
        printf("Single negative test failed!\n");
        counter++;
    }
    if (!test_all_positives()) {
        printf("All positives test failed!\n");
        counter++;
    }
    if (!test_all_negatives()) {
        printf("All negatives test failed!\n");
        counter++;
    }
    if (!test_mixed()) {
        printf("Mixed numbers test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

