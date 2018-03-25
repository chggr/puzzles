#include <math.h>
#include <stdio.h>

// Task description: Given an integer array with all numbers from 1 to N
// appearing exactly once except for one number that is missing, write a method
// to identify the missing number in O(N) runtime and O(1) space complexity.
// What if there are two numbers missing?
//
// E.g. for input array: {9, 4, 1, 7, 3, 0, 8, 6, 5}
//      the method should return 2
//
//      for input array: {9, 4, 1, 0, 3, 0, 8, 6, 5}
//      the method should return 2 and 7
//
// Solution: We know that the sum of sequence 1...N is equal to N * (N - 1) / 2.
// If there is only one number missing, we can sum up all the numbers in the
// array and subtract the result from the expected sum to identify the missing
// number.
//
// If there are two numbers missing, we will have to use both the sum and the
// product to identify which ones are missing (or other suitable function such
// as the sum of squares). We expect the sum to be equal to N * (N - 1) / 2 and
// the product to be equal to N!. If x and y are the missing numbers, we can
// form the following equations:
//
// x + y = s = N * (N - 1) / 2 - sum(array)
// x * y = p = N! - multiply(array)
//
// These equations can be solved as follows:
// x + y = s => x = s - y
// x * y = p => (s - y) * y = p => s * y - y^2 = p => y^2 - s * y + p = 0
//
// The solutions to the final equation would be:
// y = (s +- sqrt(s^2 - 4 * p)) / 2
//
// These solutions are the two numbers we are looking for. Alternatively we
// could calculate y from the equation above and then use that to calculate
// x = s - y. This algorithm is implemented below.
//
// In both cases, if the input array is large the sum / product of the elements
// might overflow the int value used below. In such cases we should use a larger
// data type such as 'unsigned long long' in C / C++ or BigInteger in Java.

// Sums all elements in the array.
int sum(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += array[i];
    }
    return result;
}

int find_one(int array[], int n) {
    return n * (n + 1) / 2 - sum(array, n);
}

// Multiplies all elements in the array, skipping zeros.
int multiply(int array[], int size) {
    int result = 1;
    for (int i = 0; i < size; i++) {
        if (array[i] == 0) continue;
        result *= array[i];
    }
    return result;
}

// Calculates the factorial.
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

struct pair {
    int first;
    int second;
};

struct pair find_two(int array[], int n) {
    int s = n * (n + 1) / 2 - sum(array, n);
    int p = factorial(n) / multiply(array, n);

    struct pair result;
    result.first = 0;
    result.second = 0;

    // Handle cases where none or just one is missing.
    if (s == 0 && p == 1) return result;
    if (s == p) {
        result.first = s;
        return result;
    }

    result.first = (s + sqrt(s * s - 4.0 * p)) / 2;
    result.second = s - result.first;
    return result;
}

int test_none_missing() {
    int array[] = {9, 4, 1, 7, 3, 2, 8, 6, 5};

    int one = find_one(array, 9);
    struct pair two = find_two(array, 9);

    return 0 == one && 0 == two.first && 0 == two.second;
}

int test_one_missing() {
    int array[] = {9, 4, 1, 7, 3, 0, 8, 6, 5};

    int one = find_one(array, 9);
    struct pair two = find_two(array, 9);

    return 2 == one && 2 == two.first && 0 == two.second;
}

int test_two_missing() {
    int array[] = {9, 4, 1, 0, 3, 0, 8, 6, 5};
    struct pair result = find_two(array, 9);
    return 7 == result.first && 2 == result.second;
}

int main() {
    int counter = 0;
    if (!test_none_missing()) {
        printf("None missing test failed!\n");
        counter++;
    }
    if (!test_one_missing()) {
        printf("One missing test failed!\n");
        counter++;
    }
    if (!test_two_missing()) {
        printf("Two missing test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

