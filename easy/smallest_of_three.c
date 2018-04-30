#include <stdio.h>

// Task description: Given three positive integers, write a method to return
// the smallest without using any comparison operators.
//
// E.g. for input integers 5, 3, 8 the method should return 3
//
// Solution: The first implementation repeatedly decrements the three numbers
// while at the same time incrementing a counter. When one or more of the
// numbers reaches zero, the counter will hold the minimum of the three. This
// approach works only for positive integers.
//
// The second implementation uses the division operator to find the smallest of
// the three numbers, taking advantage of the fact that if a < b then a / b will
// be zero. This approach also does not work for negative integers.
//
// Finally the third implementation uses a clever bit manipulation trick to find
// the minimum of two numbers. If the two numbers are a and b, the smallest of
// the two can be found as: a + ((b - a) & ((b - a) >> 31)) if we assume 32-bit
// integers. That's because:
//
// => (b - a) >> 31 evaluates to 0 if b > a or 1 if a > b
// => if b > a, then a + ((b - a) & 0) = a
// => if a > b, then a + ((b - a) & 1) = a + b - a = b
//
// Similarly we can find the maximum of a and b as: b - ((b - a) & ((b - a) >> 31))

int smallest(int a, int b, int c) {
    int result = 0;

    while (a != 0 && b != 0 && c != 0) {
        result++;
        a--;
        b--;
        c--;
    }
    return result;
}

int smallest_div(int a, int b, int c) {
    if (a / b == 0) {
        return a / c == 0 ? a : c;
    } else {
        return b / c == 0 ? b : c;
    }
}

int min(int a, int b) {
    return a + ((b - a) & ((b - a) >> 31));
}

int max(int a, int b) {
    return b - ((b - a) & ((b - a) >> 31));
}


int smallest_bit(int a, int b, int c) {
    return min(a, min(b, c));
}

int test_all_same() {
    return 5 == smallest(5, 5, 5) &&
           5 == smallest_div(5, 5, 5) &&
           5 == smallest_bit(5, 5, 5);
}

int test_two_same() {
    return 5 == smallest(5, 5, 7) &&
           5 == smallest(7, 5, 7) &&
           5 == smallest_div(5, 5, 7) &&
           5 == smallest_div(7, 5, 7) &&
           5 == smallest_bit(5, 5, 7) &&
           5 == smallest_bit(7, 5, 7);
}

int test_all_diff() {
    return 3 == smallest(3, 6, 9) &&
           3 == smallest_div(3, 6, 9) &&
           3 == smallest_bit(3, 6, 9);
}

int test_negative() {
    return -2 == smallest_bit(1, 2, -2) &&
           -2 == smallest_bit(1, -1, -2);
}

int main() {
    int counter = 0;
    if (!test_all_same()) {
        counter++;
        printf("All numbers same test failed!\n");
    }
    if (!test_two_same()) {
        counter++;
        printf("Two numbers same test failed!\n");
    }
    if (!test_all_diff()) {
        counter++;
        printf("All numbers different test failed!\n");
    }
    if (!test_negative()) {
        counter++;
        printf("Negative numbers test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

