#include <stdio.h>

// Task description: Given two arrays of integers, find a pair of values (one
// from each array) that can be swapped to give the two arrays the same sum.
//
// E.g. for arrays {1, 4, 2, 1, 1, 2} and {3, 6, 3, 3}
//      the answer is {1, 3}
//
// Solution: The first step in the implementation below is to compute the sum
// of the two arrays provided. Then we iterate through all elements of the first
// array and for each one we search in the second array for an element that is
// equal to:
//
// sum_a - a[i] + b[j] = sum_b + a[i] - b[j] =>
// 2*b[j] = sum_b - sum_a + 2*a[i] =>
// b[j] = (sum_b - sum_a + 2*a[i]) / 2
//
// The runtime complexity of the solution below is O(M*N) where M is the length
// of the first table and N is the length of the second. This can be improved to
// O(M+N) if we store the elements of the second array into a HashSet to reduce
// the time it takes to search for the required element to O(1).

struct pair {
    int one;
    int two;
};

int sum(int array[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result += array[i];
    }
    return result;
}

void sum_swap(int a[], int a_len, int b[], int b_len, struct pair* result) {
    int sum_a = sum(a, a_len);
    int sum_b = sum(b, b_len);
    if (sum_a == sum_b) return;

    int req = 0;
    for (int i = 0; i < a_len; i++) {
        req = sum_b - sum_a + 2 * a[i];
        if (req % 2 != 0) continue;
        req /= 2;

        for (int j = 0; j < b_len; j++) {
            if (b[j] == req) {
                result->one = a[i];
                result->two = b[j];
                return;
            }
        }
    }
}

int test_same_sum() {
    int a[] = {1, 4, 2, 1, 1, 2};
    int b[] = {3, 2, 3, 3};

    struct pair p;
    p.one = -1;
    p.two = -1;
    sum_swap(a, 6, b, 4, &p);
    return -1 == p.one && -1 == p.two;
}

int test_diff_sum() {
    int a[] = {1, 4, 2, 1, 1, 2};
    int b[] = {3, 6, 3, 3};

    struct pair p;
    p.one = -1;
    p.two = -1;
    sum_swap(a, 6, b, 4, &p);
    return 1 == p.one && 3 == p.two;
}

int test_neg_num() {
    int a[] = {-3, 4, 2, 1, 1, 2};
    int b[] = {3, 6, 3, 3};

    struct pair p;
    p.one = -1;
    p.two = -1;
    sum_swap(a, 6, b, 4, &p);
    return 2 == p.one && 6 == p.two;
}

int main() {
    int counter = 0;
    if (!test_same_sum()) {
        printf("Same sum test failed!\n");
        counter++;
    }
    if (!test_diff_sum()) {
        printf("Different sum test failed!\n");
        counter++;
    }
    if (!test_neg_num()) {
        printf("Negative numbers test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

