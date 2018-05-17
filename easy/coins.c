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
// where D is the number of coin denominations and N is the amount. The space
// complexity is O(N) required for the recursive stack.
//
// The second implementation uses dynamic programming to calculate the result in
// a bottom up manner. It first creates a memoization array and initializes the
// first element to one and all other elements to zero. It then populates all
// positions of the array one by one in a bottom up fashion until the result has
// been calculated. The runtime complexity of this approach is O(N * D), which
// is much better than previously. The space complexity is also O(N) for the
// memoization array.

int change(int *denom, int size, int amount) {
    if (amount == 0) return 1;
    if (amount < 0) return 0;

    int result = 0;
    for (int i = 0; i < size; i++) {
        result += change(denom, size, amount - denom[i]);
    }
    return result;
}

int change_dyn(int* denom, int size, int amount) {
    int memo[amount + 1];
    memo[0] = 1;
    for (int i = 1; i <= amount; i++) {
        memo[i] = 0;
    }

    // Fill the memo array bottom up.
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < size; j++) {
            int idx = i - denom[j];
            if (idx < 0) continue;
            memo[i] += memo[idx];
        }
    }

    return memo[amount];
}

int denom[] = {1, 5, 10, 25};

int test_one_way() {
    return 1 == change(denom, 4, 1) &&
           1 == change_dyn(denom, 4, 1);
}

int test_three_ways() {
    return 3 == change(denom, 4, 6) &&
           3 == change_dyn(denom, 4, 6);
}

int test_four_ways() {
    return 4 == change(denom, 4, 7) &&
           4 == change_dyn(denom, 4, 7);
}

int test_many_ways() {
    return 916 == change(denom, 4, 25) &&
           916 == change_dyn(denom, 4, 25);
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

