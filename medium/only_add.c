#include <stdio.h>

// Task description: Write methods to implement operations subtract, multiply
// and divide for integers using only the add operator. The results of these
// methods should also be integers.
//
// Solution: The subtract operation is the easiest of the three to implement.
// In the solution below, we first define a negate() method that can be used
// to negate any given integer. This can then be used to express subtraction as
// adding a negated number. The runtime complexity of negate() is O(n), which
// can be reduced by cleverly increasing the delta value so that the algorithm
// reaches zero faster. To do this, we first chose the delta to be 1, then 2,
// then 4, etc until the value becomes too big and causes the number to flip
// sign. At that point we reset the delta value back to 1 and repeat the
// process. This optimized approach has runtime complexity of O((log n) ^ 2).
//
// The multiply operation is equally straight forward. We just need to add the
// number m times and then change the sign of the final result accordingly. This
// operation can be expressed as follows:
// multiply(n, m) = abs(m) * n * (m < 0 ? -1 : 1)
//
// The divide operation is pretty much the reverse of multiply. We first
// compute the absolute values of the number and the divisor and then increase
// a counter to capture how many times the divisor "fits" into the number.
// The final result is negated if the number and divisor have opposite signs.

int negate(int n) {
    int out = 0;
    int sign = n > 0 ? -1 : 1;
    while (n != 0) {
        out += sign;
        n += sign;
    }
    return out;
}

int subtract(int n, int s) {
    return n + negate(s);
}

int abs(int n) {
    return n < 0 ? negate(n) : n;
}

int multiply(int n, int m) {
    int out = 0;
    int abs_m = abs(m);
    for (int i = 0; i < abs_m; i++) {
        out += n;
    }
    if (m < 0) {
        out = negate(out);
    }
    return out;
}

int divide(int n, int d) {
    if (d == 0) return 0;

    int abs_n = abs(n);
    int abs_d = abs(d);
    int product = 0;
    int out = 0;

    while (product + abs_d <= abs_n) {
        product += abs_d;
        out++;
    }
    return (n > 0 && d > 0) || (n < 0 && d < 0) ? out : negate(out);
}

int test_negate() {
    return -1 == negate(1) &&
            1 == negate(-1) &&
            0 == negate(0);
}

int test_subtract() {
    return 0 == subtract(10, 10) &&
           20 == subtract(10, -10) &&
           -20 == subtract(-10, 10) &&
           0 == subtract(-10, -10) &&
           0 == subtract(0, 0) &&
           -10 == subtract(0, 10) &&
           10 == subtract(10, 0);
}

int test_abs() {
    return 0 == abs(0) &&
           10 == abs(10) &&
           10 == abs(-10);
}

int test_multiply() {
    return 10 == multiply(5, 2) &&
           -10 == multiply(5, -2) &&
           -10 == multiply(-5, 2) &&
           10 == multiply(-5, -2) &&
           0 == multiply(5, 0) &&
           0 == multiply(0, 5);
}

int test_divide() {
    return 5 == divide(10, 2) &&
           -5 == divide(-10, 2) &&
           -5 == divide(10, -2) &&
           5 == divide(-10, -2) &&
           3 == divide(10, 3) &&
           -3 == divide(10, -3) &&
           0 == divide(10, 0) &&
           0 == divide(0, 2);
}

int main() {
    int counter = 0;
    if (!test_negate()) {
        printf("Negate test failed!\n");
        counter++;
    }
    if (!test_subtract()) {
        printf("Subtract test failed!\n");
        counter++;
    }
    if (!test_abs()) {
        printf("Abs test failed!\n");
        counter++;
    }
    if (!test_multiply()) {
        printf("Multiply test failed!\n");
        counter++;
    }
    if (!test_divide()) {
        printf("Divide test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

