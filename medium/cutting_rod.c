#include <stdio.h>

// Task description: Given a rod of length N meters and an array of prices for
// different lengths of rod, write a method to return the maximum value that can
// be obtained by cutting up the rod at various lengths and selling the pieces.
//
//                  0  1  2  3  4   5   6   7   8
// E.g for prices: {0, 1, 5, 8, 9, 10, 17, 17, 20}
//      and rod length 8 meters
//      the method should return 22 (5 + 17)
//
// Solution: The first implementation below uses a recursive approach to compute
// the maximum value that can be obtained. It attempts to cut the rod at various
// lengths and then calls itself recursively to obtain the maximum value of the
// sub-pieces. The runtime complexity of this algorithm is O(P ^ N), where P is
// the number of possible cuts and N is the rod length. The space complexity is
// O(N) for the recursive stack.
//
// The second implementation uses a bottom-up dynamic programming approach to
// improve the runtime complexity. This problem exhibits both the optimal sub-
// structure and the overlapping sub-problems properties and therefore can be
// solved using dynamic programming. We define a memoization array that stores
// for each rod length the maximum value that can be obtained. We build up the
// solution from 1 up to the given rod length and return the final result. The
// runtime complexity of this algorithm is O(N * P) where P is the number of
// possible cuts and N is the rod length. The space complexity is O(N) for the
// memoization array.

int cut_rec(int prices[], int size, int rod) {
    if (rod < 0) return -1;
    if (rod == 0) return 0;

    int max = 0;
    for (int i = 1; i < size; i++) {
        int temp = cut_rec(prices, size, rod - i);
        if (temp != -1 && temp + prices[i] > max) {
            max = temp + prices[i];
        }
    }
    return max;
}

int cut_dyn(int prices[], int size, int rod) {
    int memo[rod + 1];
    memo[0] = 0;

    for (int i = 1; i <= rod; i++) {
        int max = 0;
        for (int j = 1; j < size; j++) {
            if (i < j) continue;

            int temp = prices[j] + memo[i - j];
            if (temp > max) max = temp;
        }
        memo[i] = max;
    }
    return memo[rod];
}

int test_cut() {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    return 22 == cut_rec(prices, 9, 8) &&
           22 == cut_dyn(prices, 9, 8);
}

int test_cut_both() {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    for (int i = 0; i < 20; i++) {
        if (cut_rec(prices, 9, i) != cut_dyn(prices, 9, i)) return 0;
    }
    return 1;
}

int main() {
    int counter = 0;
    if (!test_cut()) {
        counter++;
        printf("Cut test failed!\n");
    }
    if (!test_cut_both()) {
        counter++;
        printf("Both rec and dyn cut test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

