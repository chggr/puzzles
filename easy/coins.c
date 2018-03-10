#include <stdio.h>

// Task description: Given an infinite number of quarters (25 cents), dimes (10
// cents), nickels (5 cents) and pennies (1 cent), write a method to calculate
// the number of ways of representing n cents.
//
// E.g. For amount 6 the method should return 3.
//      => {1, 1, 1, 1, 1, 1}
//      => {1, 5}
//      => {5, 1}
//
// Solution: The implementation below is recursive. At each step it iterates
// through all available coins and for each one calls itself recursively for
// the remaining amount. The runtime complexity of this approach is O(D ^ N),
// where D is the number of coin denominations and N is the amount.

int change(int *denom, int size, int amount) {
    if (amount == 0) return 1;
    if (amount < 0) return 0;

    int result = 0;
    for (int i = 0; i < size; i++) {
        result += change(denom, size, amount - denom[i]);
    }
    return result;
}

int denom[] = {1, 5, 10, 25};

int test_one_way() {
    return 1 == change(denom, 4, 1);
}

int test_three_ways() {
    return 3 == change(denom, 4, 6);
}

int test_four_ways() {
    return 4 == change(denom, 4, 7);
}

int test_many_ways() {
    return 916 == change(denom, 4, 25);
}

int main() {
    int counter = 0;
    if (!test_one_way()) {
        printf("One way coins test failed!\n");
        counter++;
    }
    if (!test_three_ways()) {
        printf("Three ways coins test failed!\n");
        counter++;
    }
    if (!test_four_ways()) {
        printf("Four ways coins test failed!\n");
        counter++;
    }
    if (!test_many_ways()) {
        printf("Many ways coins test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

