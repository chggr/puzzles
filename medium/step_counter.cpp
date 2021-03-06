#include <iostream>

// Task description: A young kid can climb up the stairs three, two or one
// steps at a time. If a staircase has a given number of steps, write a method
// that counts how many different ways the kid can climb it up.
//
// E.g. If there are 2 steps, the answer is 2: 11 2
//      If there are 3 steps, the answer is 4: 111 21 12 3
//      If there are 4 steps, the answer is 7: 1111 211 121 112 22 31 13
//      If there are 5 steps, the answer is 13: 11111 2111 1211 1121 1112 221
//                                              212 122 311 131 113 32 23
//
// Solution: The first implementation below is a simple recursive approach.
// This approach is not very efficient and its runtime complexity is O(3^n),
// because each recursive call branches out to three more calls.
//
// The second implementation uses memoization to store intermediate results
// so that the same calculations do not need to be repeated multiple times.
// Both the runtime and space complexities of this implementation are O(n).
//
// Finally, the third implementation uses an iterative dynamic programming
// approach to avoid recursive calls and further reduce space complexity to O(1)
// while retaining runtime complexity of O(n). Previous implementations were
// top-down, whereas this one is bottom-up. It is based on the observation that
// the number of possible ways to reach each step is equal to the sum of ways to
// reach step - 1 and step - 2 and step - 3. Therefore we only really need three
// variables to store the values for previous steps, reducing space complexity
// to just O(1). These variables are updated iteratively until we have computed
// the final result.

int count(int steps) {
    if (steps < 0) return 0;
    if (steps == 0) return 1;
    return count(steps - 1) + count (steps - 2) + count(steps - 3);
}

int count(int steps, int *mem) {
    if (steps < 0) return 0;
    if (steps == 0) return 1;

    if (mem[steps] == 0) {
        mem[steps] = count(steps - 1, mem) +
                     count(steps - 2, mem) +
                     count(steps - 3, mem);
    }
    return mem[steps];
}

int count_mem(int steps) {
    int mem[steps + 1] = { 0 };
    return count(steps, mem);
}

int count_dyn(int steps) {
    if (steps < 0) return 0;

    int memo[3] = { 1, 1, 2 };
    if (steps < 3) return memo[steps];

    for (int i = 3; i <= steps; i++) {
        int temp = memo[0] + memo[1] + memo[2];
        memo[0] = memo[1];
        memo[1] = memo[2];
        memo[2] = temp;
    }
    return memo[2];
}

bool test_zero_steps() {
    return count(0) == 1 &&
           count_mem(0) == 1 &&
           count_dyn(0) == 1;
}

bool test_one_step() {
    return count(1) == 1 &&
           count_mem(1) == 1 &&
           count_dyn(1) == 1;
}

bool test_two_steps() {
    return count(2) == 2 &&
           count_mem(2) == 2 &&
           count_dyn(2) == 2;
}

bool test_three_steps() {
    return count(3) == 4 &&
           count_mem(3) == 4 &&
           count_dyn(3) == 4;
}

bool test_four_steps() {
    return count(4) == 7 &&
           count_mem(4) == 7 &&
           count_dyn(4) == 7;
}

bool test_five_steps() {
    return count(5) == 13 &&
           count_mem(5) == 13 &&
           count_dyn(5) == 13;
}

bool test_many_steps() {
    for (int i = 6; i <= 30; i++) {
        int val = count(i);
        int val_mem = count_mem(i);
        int val_dyn = count_dyn(i);
        if (val != val_mem || val != val_dyn) {
            return false;
        }
    }
    return true;
}

int main() {
    int counter = 0;
    if (!test_zero_steps()) {
        std::cout << "Zero step test failed!\n";
        counter++;
    }
    if (!test_one_step()) {
        std::cout << "One step test failed!\n";
        counter++;
    }
    if (!test_two_steps()) {
        std::cout << "Two steps test failed!\n";
        counter++;
    }
    if (!test_three_steps()) {
        std::cout << "Three steps test failed!\n";
        counter++;
    }
    if (!test_four_steps()) {
        std::cout << "Four steps test failed!\n";
        counter++;
    }
    if (!test_five_steps()) {
        std::cout << "Five steps test failed!\n";
        counter++;
    }
    if (!test_many_steps()) {
        std::cout << "Many steps test failed!\n";
        counter++;
    }
    std::cout << counter << " tests failed.\n";
}

