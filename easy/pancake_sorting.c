#include <stdio.h>

// Task description: Given a stack of n pancakes, each having a different
// diameter, and a pancake flipper, write a method to sort the pancakes from
// smaller to larger. You can insert the flipper into the stack at any point,
// lift up all the pancakes above the flipper and flip them over as a unit.
// In the worse case, how many flips will it take to sort the pancakes?
//
// E.g. if the stack of pancakes is: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//      and the flipper is inserted at position 5    ^
//      the flip() operation will return: {0, 1, 2, 3, 4, 9, 8, 7, 6, 5}
//
// Solution: This is basically a sorting problem where the only operation
// allowed in the array is to reverse the elements from any given position to
// the end. Unlike a traditional sorting algorithm, which attempts to sort with
// as fewest comparisons or swaps as possible, the goal here is to sort the
// sequence with as few flips / reversals as possible.
//
// The implementation below solves this problem using a modified version of
// selection sort. For each position in the input array, it goes through the
// remainder of the array to identify the smallest element. It then performs
// two flips, one to bring the smallest element to the top of the stack and
// another one to bring it to the correct position. In the worst case, where
// the pancakes are already reverse sorted, this algorithm would require 2n - 2
// flips. That is two flips for every element except the last element that does
// not need to be flipped at all. This can be further optimized to 2n - 3 as
// follows: After we have sorted all but the last two elements, we have already
// performed 2n - 4 flips in the worst case. The final two elements can either
// be sorted, in which case we are done, or not sorted, in which case we only
// need one flip to sort them. Thus 2n - 4 + 1 = 2n - 3 in the worst case.

void flip(int array[], int pos, int size) {
    int length = size - pos;
    for (int i = 0; i < length / 2; i++) {
        int temp = array[pos + i];
        array[pos + i] = array[size - 1 - i];
        array[size - 1 - i] = temp;
    }
}

void pancake_sort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (array[min_idx] > array[j]) min_idx = j;
        }

        if (min_idx != i) {
            flip(array, min_idx, size);
            flip(array, i, size);
        }
    }
}

int are_equal(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int test_flip() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {0, 1, 2, 3, 4, 9, 8, 7, 6, 5};

    flip(input, 5, 10);
    return are_equal(input, expected, 10);
}

int test_flip_all() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    flip(input, 0, 10);
    return are_equal(input, expected, 10);
}

int test_flip_none() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    flip(input, 9, 10);
    return are_equal(input, expected, 10);
}

int test_pancake_sort() {
    int input[] = {4, 7, 2, 1, 9, 0, 6, 3, 5, 8};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    pancake_sort(input, 10);
    return are_equal(input, expected, 10);
}

int test_pancake_sort_sorted() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    pancake_sort(input, 10);
    return are_equal(input, expected, 10);
}

int test_pancake_sort_reverse_sorted() {
    int input[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    pancake_sort(input, 10);
    return are_equal(input, expected, 10);
}

int test_pancake_sort_all_equal() {
    int input[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int expected[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    pancake_sort(input, 10);
    return are_equal(input, expected, 10);
}

int main() {
    int counter = 0;
    if (!test_flip()) {
        printf("Flip test failed!\n");
        counter++;
    }
    if (!test_flip_all()) {
        printf("Flip all test failed!\n");
        counter++;
    }
    if (!test_flip_none()) {
        printf("Flip none test failed!\n");
        counter++;
    }
    if (!test_pancake_sort()) {
        printf("Pancake sort test failed!\n");
        counter++;
    }
    if (!test_pancake_sort_sorted()) {
        printf("Pancake sort already sorted test failed!\n");
        counter++;
    }
    if (!test_pancake_sort_reverse_sorted()) {
        printf("Pancake sort reverse sorted test failed!\n");
        counter++;
    }
    if (!test_pancake_sort_all_equal()) {
        printf("Pancake sort all equal test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

