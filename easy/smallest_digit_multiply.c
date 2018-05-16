#include <stdio.h>

// Task description: Given a number N, find the smallest number P such that if
// we multiply all digits of P we get N. The result P should have at least two
// digits.
//
// E.g. for input number 36, the method should return 49
//      for input number 13, the method should return 0
//
// Solution: A brute force solution would be to go through all numbers P greater
// than 11 and for each number check whether the product of its digits is equal
// to the given number N. The runtime complexity of this approach is O(N).
//
// The implementation below is much more efficient. We first calculate the
// minimum number of digits required for P and then recursively place digits at
// each position until we have identified the solution.

// Returns the minimum number of digits required for P (at minimum 2).
int digit_count(int num) {
    int result = 2;
    int temp = 9 * 9;
    while (num > temp) {
        result++;
        temp *= 9;
    }
    return result;
}

// Converts an array of digits to integer.
int to_int(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result *= 10;
        result += array[i];
    }
    return result;
}

int find_rec(int array[], int size, int index, int target) {
    if (index == size) return target == 1;

    // Try all possible digits for this position.
    for (int i = 1; i <= 9; i++) {
        if (target % i != 0) continue;

        array[index] = i;
        if (find_rec(array, size, index + 1, target / i)) return 1;
    }
    return 0;
}

int find(int num) {
    int count = digit_count(num);
    int array[count];
    return find_rec(array, count, 0, num) ? to_int(array, count) : 0;
}

int test_found() {
    return 11 == find(1) &&
           17 == find(7) && 
           49 == find(36) &&
           455 == find(100);
}

int test_not_found() {
    return 0 == find(13) &&
           0 == find(29) &&
           0 == find(233);
}

int main() {
    int counter = 0;
    if (!test_found()) {
        counter++;
        printf("Found test failed!\n");
    }
    if (!test_not_found()) {
        counter++;
        printf("Not found test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

