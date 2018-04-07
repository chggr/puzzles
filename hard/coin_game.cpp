#include <iostream>

using namespace std;

// Task description: There is a row of n coins (where n is even) with different
// values and two players. Each player can take either the first or the last
// coin from the row. Determine the maximum possible amount of money that the
// first player can definitely win.
//
// E.g. for coins {8, 15, 3, 7}, the answer is 7 + 15 = 22
//
// Solution: The first implementation below is a recursive approach that
// calculates the best possible score when picking either the left or the right
// coin and returns the maximum of the two. The same recursive method is used to
// simulate the opponent's and our next move once the right or left coin has
// been picked. The runtime complexity of this approach is O(4^N), where N is
// the number of coins available. That's because at each step we call the
// recursive method four times. The space complexity is O(N) because the depth
// of recursion is equal to the number of coins available.
//
// Unfortunately this implementation is quite wasteful because the same results
// are computed many times. Performance can be greatly improved by using a map
// to store intermediate results for given start and end indices. This top down
// memoization approach ensures that we calculate each result only once and
// reuse it when necessary. Therefore the runtime complexity is now reduced to
// just O(N^2), at the expense of space complexity which now increases to O(N^2).
//
// The third implementation is a bottom up dynamic programming approach where
// a table is used to store the intermediate results and the final solution is
// built from the bottom up. It is based on the observation that to select the
// coin at the start or the end of the array, we need to calculate the value
// of each move and take the maximum. The value of taking the coin at the start
// will be equal to that coin's value plus the minimum of the moves available
// once the opponent has played. We need to take the minimum because we assume
// that the opponent is as smart as we are and therefore their move will attempt
// to put us in the worst possible position. In a similar fashion we calculate
// the value of taking the coin at the end and choose the move that will yield
// the best result. The formula below summarizes our approach:
//
// MOVE(start, end) = MAX(Vstart + MIN(MOVE(start + 2, end),
//                                     MOVE(start + 1, end - 1)),
//                        Vend + MIN(MOVE(start + 1, end - 1),
//                                   MOVE(start, end - 2)))
//
// In the dynamic programming implementation there are two base cases:
// (1) if start == end, then return the coin at start.
// (2) if start == end - 1, then return the maximum of coins at start and end.
//
// Using these base cases and the aforementioned equation, we create a 2D memo
// matrix and start filling it in from the diagonal upwards. The elements at the
// diagonal will be equal to the coin values. The elements next to the diagonal
// will be equal to the maximum of adjacent coins as mentioned in the second
// base case. The final result will be stored at the top right element. The
// runtime complexity of this approach is O(N^2) and the space complexity is
// O(N^2) for the memo matrix.
//
// For example coins {8, 15, 3, 7} the memo matrix will be filled in as follows:
//     8 15 11 22
//     0 15 15 18
//     0  0  3  7
//     0  0  0  7

class Result {
    public:
        int value;
        int move;
        Result(int v, int m) : value(v), move(m) {};
};

Result max_value_rec(int coins[], int start, int end) {
    if (start > end) return Result(0, -1);
    if (start == end) return Result(coins[start], start);

    // Best score if we play left.
    Result opponent = max_value_rec(coins, start + 1, end);
    Result next = max_value_rec(coins,
            opponent.move == start + 1 ? start + 2: start + 1,
            opponent.move == end ? end - 1 : end);
    int left = coins[start] + next.value;

    // Best score if we play right.
    opponent = max_value_rec(coins, start, end - 1);
    next = max_value_rec(coins,
            opponent.move == start ? start + 1 : start,
            opponent.move == end - 1 ? end - 2 : end - 1);
    int right = coins[end] + next.value;

    return left > right ? Result(left, start) : Result(right, end);
}

int max (int a, int b) {
    return a > b ? a : b;
}

int min (int a, int b) {
    return a > b ? b : a;
}

int max_value_dyn(int coins[], int size) {
    if (size == 0) return 0;

    // Create memo array and fill it with zeros.
    int memo[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            memo[i][j] = 0;
        }
    }

    // For every gap between start and end, fill in the matrix.
    for (int k = 0; k < size; k++) {
        for (int i = 0, j = k; j < size; i++, j++) {

            // MOVE(start + 2, end)
            int a = (i + 2) <= j ? memo[i + 2][j] : 0;

            // MOVE(start + 1, end - 1)
            int b = (i + 1) <= (j - 1) ? memo[i + 1][j - 1] : 0;

            // MOVE(start, end - 2)
            int c = i <= (j - 2) ? memo[i][j - 2] : 0;

            memo[i][j] = max(coins[i] + min(a, b), coins[j] + min(b, c));
        }
    }
    return memo[0][size - 1];
}

bool test_empty() {
    int coins[] = {};
    Result rec = max_value_rec(coins, 0, 0);
    return 0 == rec.move && 0 == rec.value &&
           0 == max_value_dyn(coins, 0);
}

bool test_one_element() {
    int coins[] = {5};
    Result rec = max_value_rec(coins, 0, 0);
    return 0 == rec.move && 5 == rec.value &&
           5 == max_value_dyn(coins, 1);
}

bool test_two_elements() {
    int coins[] = {5, 10};
    Result rec = max_value_rec(coins, 0, 1);
    return 1 == rec.move && 10 == rec.value &&
           10 == max_value_dyn(coins, 2);
}

bool test_small() {
    int coins[] = {8, 15, 3, 7};
    Result rec = max_value_rec(coins, 0, 3);
    return 22 == rec.value && 3 == rec.move &&
           22 == max_value_dyn(coins, 4);
}

bool test_large() {
    int coins[] = {6, 9, 1, 2, 16, 8};
    Result rec = max_value_rec(coins, 0, 5);
    return 23 == rec.value && 0 == rec.move &&
           23 == max_value_dyn(coins, 6);
}

int main() {
    int counter = 0;
    if (!test_empty()) {
        counter++;
        cout << "Empty array test failed!" << endl;
    }
    if (!test_one_element()) {
        counter++;
        cout << "One element array test failed!" << endl;
    }
    if (!test_two_elements()) {
        counter++;
        cout << "Two elements array test failed!" << endl;
    }
    if (!test_small()) {
        counter++;
        cout << "Small array test failed!" << endl;
    }
    if (!test_large()) {
        counter++;
        cout << "Large array test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

