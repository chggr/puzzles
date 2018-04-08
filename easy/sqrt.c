#include <math.h>
#include <stdio.h>

// Task description: Given a positive non-zero number, write a method to return
// its square root without using any library methods.
//
// E.g. for number 2.0 the method should return 1.41421
//
// Solution: The implementation below uses the babylonian method to calculate
// the square root of the given number. It starts with a rough estimate and
// continuously refines it until the error is less than the required precision.
// According to this method, the next approximation x' is based on the current
// approximation: x' = (x + number / x) / 2.

int accept(double a, double b, double precision) {
    double error = a - b;
    if (error < 0) error = -error;
    return error < precision;
}

double square_root(double number, double precision) {
    if (number < 0.0) return -1;

    // Initial approximation.
    double result = number / 2;

    while (!accept(number, result*result, precision)) {
        result = (result + number/result) / 2;
    }
    return result;
}

double PREC = 0.00001;

int test_negative() {
    return -1.0 == square_root(-1.0, PREC) &&
           -1.0 == square_root(-2.0, PREC) &&
           -1.0 == square_root(-3.0, PREC);
}

int test_zero() {
    return 0.0 == square_root(0.0, PREC);
}

int test_squares() {
    return accept(1.0, square_root(1.0, PREC), PREC) &&
           accept(2.0, square_root(4.0, PREC), PREC) &&
           accept(3.0, square_root(9.0, PREC), PREC) &&
           accept(4.0, square_root(16.0, PREC), PREC) &&
           accept(5.0, square_root(25.0, PREC), PREC);
}

int test_non_squares() {
    for (double num = 0.0; num < 1000.0; num += 0.001) {
        double expected = sqrt(num);
        double actual = square_root(num, PREC);
        if (!accept(expected, actual, 0.0001)) return 0;
    }
    return 1;
}

int main() {
    int counter = 0;
    if (!test_negative()) {
        counter++;
        printf("Negative test failed!\n");
    }
    if (!test_zero()) {
        counter++;
        printf("Zero test failed!\n");
    }
    if (!test_squares()) {
        counter++;
        printf("Squares test failed!\n");
    }
    if (!test_non_squares()) {
        counter++;
        printf("Non squares test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

