#include <stdio.h>

// Task description: Write a swap() method that will swap two numbers without
// using a temporary variable. Can this be done in more than one ways?
//
// E.g. For a = 10 and b = 20, calling swap() will result in a = 20 and b = 10
//
// Solution: This task can be solved in two possible ways: the first method
// uses simple arithmetic, whereas the second uses bit wise operators.
//
// If we denote a0 and b0 as the original values of a and b respectively, we
// can swap them using the following equations:
// a = a + b = a0 + b0
// b = a - b = a0 + b0 - b0 = a0
// a = a - b = a0 + b0 - a0 - b0
//
// A similar solution can be implemented with bit manipulation as follows. This
// solution is better, since it works for more data types than integers.
// For example if a = 0b1100 and b = 0b0011:
// a = a^b = 0b1100 ^ 0b0011 = 0b1111
// b = a^b = 0b1111 ^ 0b0011 = 0b1100
// a = a^b = 0b1111 ^ 0b1100 = 0b0011

void swap(int* a, int* b) {
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}

void swap_bits(int* a, int* b) {
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

int test_both_zero() {
    int a = 0;
    int b = 0;
    swap(&a, &b);

    int c = 0;
    int d = 0;
    swap_bits(&a, &b);

    return a == 0 && b == 0 &&
           c == 0 && d == 0;
}

int test_both_positive() {
    int a = 10;
    int b = 20;
    swap(&a, &b);

    int c = 30;
    int d = 40;
    swap_bits(&c, &d);

    return a == 20 && b == 10 &&
           c == 40 && d == 30;
}

int test_both_negative() {
    int a = -10;
    int b = -20;
    swap(&a, &b);

    int c = -30;
    int d = -40;
    swap_bits(&c, &d);

    return a == -20 && b == -10 &&
           c == -40 && d == -30;
}

int test_positive_negative() {
    int a = 10;
    int b = -20;
    swap(&a, &b);

    int c = 30;
    int d = -40;
    swap_bits(&c, &d);

    return a == -20 && b == 10 &&
           c == -40 && d == 30;
}

int test_positive_zero() {
    int a = 10;
    int b = 0;
    swap(&a, &b);

    int c = 30;
    int d = 0;
    swap_bits(&c, &d);

    return a == 0 && b == 10 &&
           c == 0 && d == 30;
}

int test_negative_zero() {
    int a = 0;
    int b = -20;
    swap(&a, &b);

    int c = 0;
    int d = -40;
    swap_bits(&c, &d);

    return a == -20 && b == 0 &&
           c == -40 && d == 0;
}

int main() {
    int counter = 0;
    if (!test_both_zero()) {
        printf("Both numbers zero test failed!\n");
        counter++;
    }
    if (!test_both_positive()) {
        printf("Both numbers positive test failed!\n");
        counter++;
    }
    if (!test_both_negative()) {
        printf("Both numbers negative test failed!\n");
        counter++;
    }
    if (!test_positive_negative()) {
        printf("One number positive one negative test failed!\n");
        counter++;
    }
    if (!test_positive_zero()) {
        printf("One number positive one zero test failed!\n");
        counter++;
    }
    if (!test_negative_zero()) {
        printf("One number negative one zero test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}


