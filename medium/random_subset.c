#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task description: Given an array of n integers and a perfect random number
// generator, write a method to return a set of m integers (m < n) where each
// number has equal probability of being chosen.
//
// Solution: The implementation below initially copies the first m elements of
// the original array to the target array. It then iterates through the
// remaining elements of the original array and for each one generates a random
// number between zero and its index inclusive. If this random number is less
// than m, then that position in the target array is set to be equal to the
// element in the original array. This algorithm guarantees that each number in
// the original array has equal probability of being chosen.

void subset(int a[], int a_size, int b[], int b_size) {
    if (a_size < b_size) return;

    for (int i = 0; i < b_size; i++) {
        b[i] = a[i];
    }

    for (int i = b_size; i < a_size; i++) {
        int idx = rand() % (i + 1);
        if (idx < b_size) b[idx] = a[i];
    }
}

int test_subset_bigger() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[20] = {0};

    subset(a, 10, b, 20);
    for (int i = 0; i < 20; i++) {
        if (b[i] != 0) return 0;
    }
    return 1;
}

int test_subset() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[5] = {-1};

    subset(a, 10, b, 5);
    int shuffled = 0;
    for (int i = 0; i < 5; i++) {
        int found = 0;
        for (int j = 0; j < 10; j++) {
            if (b[i] == a[j]) {
                found = 1;
                shuffled += j!= i;
                break;
            }
        }
        if (!found) return 0;
    }
    return shuffled > 0;
}

int main() {
    srand(time(NULL));
    int counter = 0;
    if (!test_subset_bigger()) {
        printf("Subset bigger test failed!\n");
        counter++;
    }
    if (!test_subset()) {
        printf("Subset test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

