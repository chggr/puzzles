#include <stdio.h>

// Task description: Given an array of N integers, write a method to return an
// output array such that the element at position i will be equal to the product
// of all elements of the input array except the element at i. Can this be done
// in O(N) without using the division operator?
//
// E.g. for input array: {4, 7, 3, 1, 5}
//      the method should return: {105, 60, 140, 420, 84}
//
// Solution: The implementation below first populates the output array from left
// to right so that each position holds the product of all elements at its left.
// Then it goes through the array once more from right to left, keeping track of
// the running product (i.e. product of all elements to the right) and
// populating each position by multiplying the running product with the value
// calculated previously. The runtime complexity of this approach is O(N), where
// N is the number of elements in the input array. The space complexity is O(1).

void calculate(int input[], int output[], int size) {
    int product = 1;
    for (int i = 0; i < size; i++) {
        output[i] = product;
        product *= input[i];
    }

    product = 1;
    for (int i = size - 1; i >= 0; i--) {
        output[i] *= product;
        product *= input[i];
    }
}

int are_equal(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int test_zeros() {
    int input[] = {0, 0, 0, 0, 0};
    int expected[] = {0, 0, 0, 0, 0};
    int output[5];

    calculate(input, output, 5);
    return are_equal(output, expected, 5);
}

int test_ones() {
    int input[] = {1, 1, 1, 1, 1};
    int expected[] = {1, 1, 1, 1, 1};
    int output[5];

    calculate(input, output, 5);
    return are_equal(output, expected, 5);
}

int test_positive() {
    int input[] = {4, 7, 3, 1, 5};
    int expected[] = {105, 60, 140, 420, 84};
    int output[5];

    calculate(input, output, 5);
    return are_equal(output, expected, 5);
}

int test_negative() {
    int input[] = {-4, 7, -3, 1, -5};
    int expected[] = {105, -60, 140, -420, 84};
    int output[5];

    calculate(input, output, 5);
    return are_equal(output, expected, 5);
}

int test_one_zero() {
    int input[] = {4, 7, 0, 1, 5};
    int expected[] = {0, 0, 140, 0, 0};
    int output[5];

    calculate(input, output, 5);
    return are_equal(output, expected, 5);
}

int main() {
    int counter = 0;
    if (!test_zeros()) {
        printf("Zeros test failed!\n");
        counter++;
    }
    if (!test_ones()) {
        printf("Ones test failed!\n");
        counter++;
    }
    if (!test_positive()) {
        printf("Positive test failed!\n");
        counter++;
    }
    if (!test_negative()) {
        printf("Negative test failed!\n");
        counter++;
    }
    if (!test_one_zero()) {
        printf("One zero test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

