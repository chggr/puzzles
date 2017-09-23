#include <math.h>
#include <stdio.h>

// Task description: Given a positive integer, write a method to check whether
// it is a prime number or not. A prime number is a number greater than 1 that
// has no positive divisors other than 1 and itself.
//
// Solution: A common approach is to follow the definition of a prime number
// and loop through all numbers from 2 up to the given integer. For each number
// check whether the remainder of the division is zero and return false if yes.
//
// Although this approach is very common, it is also hugely inefficient. We
// only really need to loop from 2 up to and including the square root of the
// given integer. This is sufficient because, for every number x that divides
// the given integer evenly, there will be a complement y such that x * y = n. 
// If x is greater than the square root of n then y should be less than the
// square root of n. Therefore our algorithm would catch y and return false.

int is_prime(int number) {
    if (number < 2) return 0;

    int root = sqrt(number);
    for (int i = 2; i <= root; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

int test_prime() {
    return is_prime(7) && is_prime(2137); 
}

int test_non_prime() {
    return !is_prime(8) && !is_prime(4453);
}

int main() {
    int counter = 0;
    if (!test_prime()) {
        printf("Prime test failed!\n");
        counter++;
    }
    if (!test_non_prime()) {
        printf("Non prime test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

