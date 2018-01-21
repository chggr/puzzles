#include <stdio.h>

// Task description: Write a method to detect whether a given integer is a power
// of ten or not.
//
// E.g. For integers: 1, 10, 100, 1000
//      the method should return true.
//
//      For integers: -1, -10, 1010, 1234
//      the method should return false.
//
// Solution: The implementation below immediately returns false if the given
// integer is less or equal to zero. It then continuously divides the number by
// ten until there is a remainder. The number is power of ten only when the
// remainder is equal to one.

int power_of_ten(int num) {
    if (num <= 0) return 0;

    while (num % 10 == 0) num /= 10;
    return num == 1;
}

int test_positive() {
    return power_of_ten(1) &&
           power_of_ten(10) &&
           power_of_ten(100) &&
           power_of_ten(1000) &&
           power_of_ten(10000) &&
           power_of_ten(100000);
}

int test_negative() {
    return !power_of_ten(0) &&
           !power_of_ten(2) &&
           !power_of_ten(15) &&
           !power_of_ten(-1) &&
           !power_of_ten(-10) &&
           !power_of_ten(1234) &&
           !power_of_ten(1010);
}

int main() {
    int counter = 0;
    if (!test_positive()) {
        printf("Power of ten test failed!\n");
        counter++;
    }
    if (!test_negative()) {
        printf("Not power of ten test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

