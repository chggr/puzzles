#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task description: Given an array of integers and a perfect random number
// generator, write a method to perfectly shuffle the array so that each of the
// size! combinations comes up equally likely.
//
// Solution: It is very tricky to come up with an algorithm that perfectly
// shuffles the array. The implementation below goes through all elements in
// the array and for each element uses the random number generator to pick an
// element at a smaller index and swap them. This algorithm is guaranteed to
// shuffle the input array perfectly.

// Generates random number from 0 to ceiling inclusive.
int generate(int ceiling) {
    return rand() % (ceiling + 1);
}

void shuffle(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int idx = generate(i);
        int temp = array[i];
        array[i] = array[idx];
        array[idx] = temp;
    }
}

int test_shuffle() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(array, 10);

    int shuffled = 0;
    for (int i = 0; i < 10; i++) {
        int found = 0;
        for (int j = 0; j < 10; j++) {
            if (array[j] == i) {
                found = 1;
                shuffled += j != i;
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
    if (!test_shuffle()) {
        printf("Shuffle test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

