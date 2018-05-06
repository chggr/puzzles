#include <stdio.h>

// Task description: Analyze the complexity (big O) of each of the five
// recursive functions below.
//
// Solution:
//
//     function_a: This function is calling itself once and executes exactly
//     n times before reaching the base case, thus is linear O(n).
//
//     function_b: This function is again calling itself once and executes
//     exactly n/2 times before reaching the base case, thus is linear O(n).
//
//     function_c: This function is calling itself once but each time divides
//     n by three, thus will execute log3(n) times and is logarithmic O(logn).
//
//     function_d: This function calls itself twice thus will execute 2^n
//     before reaching the base case and thus is exponential O(2^n);
//
//     function_e: This function executes a for loop before it calls itself.
//     The for loop is linear but is called recursively n times thus the
//     overall complexity is O(n^2).

int function_a(int n) {
    return n <= 0 ? 1 : function_a(n - 1) + 1;
}

int function_b(int n) {
    return n <= 0 ? 1 : function_b(n - 2) + 1;
}

int function_c(int n) {
    return n <= 0 ? 1 : function_c(n / 3) + 1;
}

int function_d(int n, int o, int p) {
    if (n <= 0) printf("%d, %d\n", o, p);
    else {
        function_d(n - 1, o + 1, p);
        function_d(n - 1, o, p + 1);
    }
}

int function_e(int n) {
    for (int i = 0; i < n; i += 2) {
        printf("%d\n", i);
    }
    return n <= 0 ? 1 : function_e(n - 2) + 1;
}

int main() { }

