#include <iostream>

// Task description: Write a method to compute the nth number in the Fibonacci
// sequence. The Fibonacci sequence is a sequence where the first two numbers
// are by definition 0 and 1 and each subsequent number is the sum of the
// previous two. The first few Fibonacci numbers are:
// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144
//
// E.g. For n = 8, the answer is 21.
//
// Solution: The first implementation below is the simplest possible recursive
// implementation. This approach is very inefficient, as intermediate results
// are calculated multiple times and the overall runtime complexity is O(2^n).
// The runtime complexity can be derived by visualizing the calculations as
// a tree. Each calculation node will have two children and the depth of the
// tree will be n, which gives us roughly O(2^n). Space complexity is O(n).
//
// The second implementation uses memoization to store intermediate results and
// avoid recalculating the same result multiple times. This approach is much
// faster and both its runtime and space complexities are just O(n).
//
// The final approach is iterative, looping from 2 to n and updating variables
// n2 and n1 until the final result is calculated. This is the most effective
// approach with O(n) runtime complexity and O(1) space complexity.

long fibonacci(long n) {
    return n == 0 || n == 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

long fibonacci(long n, long *memo) {
    if (n == 0 || n == 1) return n;
    if (memo[n] == 0) {
        memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo);
    }
    return memo[n];
}

long fibonacci_mem(long n) {
    long memo[n + 1] = { 0 };
    return fibonacci(n, memo);
}

long fibonacci_it(long n) {
    if (n == 0 || n == 1) return n;

    long n2 = 0;
    long n1 = 1;
    long result = 0;
    for (int i = 2; i <= n; i++) {
        result = n2 + n1;
        n2 = n1;
        n1 = result;
    }
    return result;
}

bool test_recursive() {
    return 0 == fibonacci(0) &&
           1 == fibonacci(1) &&
           21 == fibonacci(8);
}

bool test_memoization() {
    return 0 == fibonacci_mem(0) &&
           1 == fibonacci_mem(1) &&
           21 == fibonacci_mem(8);
}

bool test_iterative() {
    return 0 == fibonacci_it(0) &&
           1 == fibonacci_it(1) &&
           21 == fibonacci_it(8);
}

int main() {
    int counter = 0;
    if (!test_recursive()) {
        std::cout << "Recursive Fibonacci test failed!" << std::endl;
        counter++;
    }
    if (!test_memoization()) {
        std::cout << "Memoization Fibonacci test failed!" << std::endl;
        counter++;
    }
    if (!test_iterative()) {
        std::cout << "Iterative Fibonacci test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

