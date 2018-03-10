#include <stdio.h>

// Task description: Given an infinite number of coins of various denominations,
// write a method to calculate the minimum number of coins required to make a
// given amount.
//
// E.g. for coin denominations {1, 5, 10, 25} and amount 123
//      the method should return 9 (i.e. 4 * 25 + 2 * 10 + 3 * 1)
//
// Solution: The first implementation below is a greedy iterative algorithm that
// calculates the minimum number of coins required to make the given amount as
// follows: In each iteration, it uses the largest denomination that is less or
// equal to the remaining amount. This greedy approach works well only when the
// coin denominations are canonical, but breaks if the denominations are
// arbitrary. For example if the denominations are {1, 3, 4} and the target
// amount is 6, this greedy algorithm will return 3 coins (4, 1, 1) whereas the
// correct answer is two (3, 3). The space complexity of this algorithm is O(1)
// and the runtime complexity is O(N * D) where N is the given amount and D is
// the denominations.
//
// The second implementation is recursive and can be used both with canonical
// and arbitrary coin denominations. At each step it iterates through the given
// denominations and calls itself recursively using each one of them. The
// runtime complexity of this approach is O(D ^ N) and the space complexity is
// O(N) where D is the number of denominations and N is the given amount. The
// recursion will potentially reach up to the Nth level and at each level it
// recursively calls itself D times. This runtime is very inefficient and not
// practical even for small amounts.
//
// Finally, the third implementation uses an iterative dynamic programming
// approach to avoid recursive calls and reduce runtime complexity to O(N * D),
// while maintaining the space complexity of O(N). Both previous implementations
// were bottom-down, whereas this one is bottom-up. It defines an array of size
// N that will hold the minimum number of coins required at each position. To
// calculate the value of each position, the algorithm picks the minimum of the
// values at the current index minus each denomination and adds one. At the end
// of this process, the array will be populated with the minimum number of coins
// at each position and with -1 for amounts that cannot be made with the given
// denominations.

int change_greedy(int *denom, int size, int amount) {
    int result = 0;
    int flag = 1;
    while (amount > 0 && flag) {
        flag = 0;
        for (int i = size - 1; i >= 0; i--) {
            if (amount >= denom[i]) {
                amount -= denom[i];
                result++;
                flag = 1;
                break;
            }
        }
    }
    return amount == 0 ? result : 0;
}

int change_rec(int *denom, int size, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return -1;

    int min = -1;
    for (int i = 0; i < size; i++) {
        int temp = change_rec(denom, size, amount - denom[i]);
        if (temp == -1) continue;
        if (min == -1 || temp < min) min = temp;
    }
    return min == -1 ? -1 : min + 1;
}

int change_dyn(int *denom, int size, int amount) {
    if (amount <= 0) return 0;

    int memo[amount + 1];
    memo[0] = 0;
    for (int i = 1; i <= amount; i++) {
        memo[i] = -1;
        for (int j = 0; j < size; j++) {
            int idx = i - denom[j];
            if (idx < 0 || memo[idx] == -1) continue;
            if (memo[i] == -1 || memo[i] > memo[idx] + 1) {
                memo[i] = memo[idx] + 1;
            }
        }
    }
    return memo[amount];
}

int canonical[] = {1, 5, 10, 25};
int arbitrary[] = {1, 3, 4, 10};

int test_negative() {
    return 0 == change_greedy(canonical, 4, -10) &&
           -1 == change_rec(canonical, 4, -10) &&
           0 == change_dyn(canonical, 4, -10);
}

int test_zero() {
    return 0 == change_greedy(canonical, 4, 0) &&
           0 == change_rec(canonical, 4, 0) &&
           0 == change_dyn(canonical, 4, 0);
}

int test_canonical_one() {
    return 1 == change_greedy(canonical, 4, 1) &&
           1 == change_rec(canonical, 4, 1) &&
           1 == change_dyn(canonical, 4, 1);
}

int test_canonical_two() {
    return 2 == change_greedy(canonical, 4, 6) &&
           2 == change_rec(canonical, 4, 6) &&
           2 == change_dyn(canonical, 4, 6);
}

int test_canonical_three() {
    return 3 == change_greedy(canonical, 4, 16) &&
           3 == change_rec(canonical, 4, 16) &&
           3 == change_dyn(canonical, 4, 16);
}

int test_canonical_many() {
    return 9 == change_greedy(canonical, 4, 123) &&
           9 == change_dyn(canonical, 4, 123);
}

int test_arbitrary_two() {
    return 3 == change_greedy(arbitrary, 4, 6) &&
           2 == change_rec(arbitrary, 4, 6) &&
           2 == change_dyn(arbitrary, 4, 6);
}

int test_none() {
    int denom[] = {4, 15, 22, 51};
    return 0 == change_greedy(denom, 4, 17) &&
           -1 == change_rec(denom, 4, 17) &&
           -1 == change_dyn(denom, 4, 17);
}

int main() {
    int counter = 0;
    if (!test_negative()) {
        printf("Negative amount test failed!\n");
        counter++;
    }
    if (!test_zero()) {
        printf("Zero amount test failed!\n");
        counter++;
    }
    if (!test_canonical_one()) {
        printf("One coin canonical test failed!\n");
        counter++;
    }
    if (!test_canonical_two()) {
        printf("Two coins canonical test failed!\n");
        counter++;
    }
    if (!test_canonical_three()) {
        printf("Three coins canonical test failed!\n");
        counter++;
    }
    if (!test_canonical_many()) {
        printf("Many coins canonical test failed!\n");
        counter++;
    }
    if (!test_arbitrary_two()) {
        printf("Two coins arbitrary test failed!\n");
        counter++;
    }
    if (!test_none()) {
        printf("No coin test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

