#include <stdio.h>

// Task description: Given a positive integer n, write a method to calculate
// the number of trailing zeros of n! (factorial). Ensure the algorithm scales
// well for large numbers of n.
//
// Solution: The simplest approach would be to actually compute n! and then
// count the number of trailing zeroes by continuously dividing by 10 until
// the remainder of the division is not zero. This would work but involves
// calculating n! which is very costly. Moreover, n! takes huge values even
// for relatively small n, thus quickly exceeding the bounds of an int.
//
// The implementation below is instead based on the observation that a trailing
// zero can only be created by multiples of 10, which are themselves created as
// multiples of pairs of fives and twos. Therefore to count the number of
// trailing zeros we simply need to count the number of multiple of fives in
// the factorial.

int fives(int n) {
    int count = 0;
    while (n % 5 == 0) {
        count++;
        n /= 5;
    }
    return count;
}

int factorial_zeros(int n) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        count += fives(i);
    }
    return count;
}

int test_fives() {
    return 0 == fives(19) &&
           1 == fives(20) &&
           2 == fives(50) &&
           3 == fives(250);
}

int test_factorial_zeros() {
    return 2 == factorial_zeros(13) &&
           3 == factorial_zeros(15) &&
           4 == factorial_zeros(20);
}

int main() {
    int counter = 0;
    if (!test_fives()) {
        printf("Fives test failed!\n");
        counter++;
    }
    if (!test_factorial_zeros()) {
        printf("Factorial zeros test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

