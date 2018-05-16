#include <stdio.h>

// Task description: Given a positive integer N, write a method to return the
// count of numbers from 1 to N that do not contain digit 3 in their decimal
// representation.
//
// e.g. for input number 9, the method should return 8
//      for input number 99, the method should return 80
//
// Solution: A brute force approach would be to go through all numbers from 1
// to N, check the decimal representation of each one and increase a counter
// if digit 3 is not included. The runtime complexity of this approach is
// O(N * logN) because for each number we need to go through logN digits to
// detect digit 3.
//
// The implementation below is much more efficient and directly calculates the
// output using a recursive approach. The base case is if the number is less
// than 10, i.e. consists of only one digit. In all other cases we first
// calculate the most significant digit (MSD) and the power of ten of that
// digit. We then recursively return the count as follows:
//
// (a) If the MSD is three, the count is equal to the count of the MSD times the
//     power minus 1. For example count(35) = count (3 * 10 - 1) = count(29),
//     because all numbers greater than 29 are disqualified.
//
// (b) If the MSD is not three, the count can be broken down into two pieces:
//     the count for this digit + the count of the remainder. For example,
//     count(578) = count(5) * count(99) + count(5) + count(78). The first two
//     terms represent the total count for this digit including numbers such as
//     100, 200, 400, 500. The third term represents the count of the remainder.

int count(int num) {
    if (num < 0) return 0;
    if (num < 3) return num;
    if (num < 10) return num - 1;

    int msd = 10;
    int pow = 1;

    while (msd >= 10) {
        pow *= 10;
        msd = num / pow;
    }

    return msd == 3 ? count(msd * pow - 1) :
        count(msd) * count(pow - 1) + count(msd) + count(num % pow);
}

int test_negative() {
    return 0 == count(-1) && 0 == count(-10) && 0 == count(-100);
}

int test_single_digit() {
    return 0 == count(0) && 1 == count(1) && 2 == count(2) &&
           2 == count(3) && 3 == count(4) && 4 == count(5) &&
           5 == count(6) && 6 == count(7) && 8 == count(9);
}

int test_double_digit() {
    return 9 == count(10) && 31 == count(45) && 80 == count(99);
}

int test_multi_digit() {
    return 101 == count(123) && 284 == count(456) && 385 == count(578);
}

int main() {
    int counter = 0;
    if (!test_negative()) {
        counter++;
        printf("Negative test failed!\n");
    }
    if (!test_single_digit()) {
        counter++;
        printf("Single digit test failed!\n");
    }
    if (!test_double_digit()) {
        counter++;
        printf("Double digit test failed!\n");
    }
    if (!test_multi_digit()) {
        counter++;
        printf("Multi digit test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

