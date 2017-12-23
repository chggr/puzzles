#include <stdio.h>

// Task description: In the game of mastermind, one player selects four balls
// of different or similar color and the second player needs to guess what color
// balls have been chosen. There are four possible colors: red (R), green (G),
// blue (B) and yellow (Y). Upon each guess, the first player needs to declare
// the number of hits and pseudo hits. A hit means that the correct color has
// been identified on the correct position. A pseudo hit means that the correct
// color was identified but on the wrong position. For a given ball selection
// and guess, write methods to return the number of hits and pseudo hits.
//
// E.g. if the selection is RGBY and the guess is RRGG
//      there is one hit (first position) and one pseudo hit.
//
// Solution: Calculating the number of hits is fairly easy, we just need to go
// through the selection and the guess and count how many positions are occupied
// by the same color. To calculate the number of pseudo hits, we need to ensure
// that the positions where there are hits are excluded and that each guessed
// color is used only once. To achieve this, we create a frequency table and use
// that to count the number of pseudo hits.

int hits(char actual[], char guess[], int size) {
    int hits = 0;
    for (int i = 0; i < size; i++) {
        if (actual[i] == guess[i]) hits++;
    }
    return hits;
}

int code(char color) {
    if (color == 'R') return 0;
    if (color == 'G') return 1;
    if (color == 'B') return 2;
    if (color == 'Y') return 3;
    return -1;
}

int pseudo(char actual[], char guess[], int size) {
    int freq[4] = { 0 };
    for (int i = 0; i < size; i++) {
        if (actual[i] == guess[i]) continue;
        freq[code(guess[i])]++;
    }

    int pseudo = 0;
    for (int i = 0; i < size; i++) {
        if (actual[i] == guess[i]) continue;
        if (freq[code(actual[i])] > 0) {
            pseudo++;
            freq[code(actual[i])]--;
        }
    }
    return pseudo;
}

int test_no_hits_no_pseudo() {
    char actual[] = {'R', 'R', 'R', 'R'};
    char guess[] = {'G', 'G', 'G', 'G'};
    return 0 == hits(actual, guess, 4) &&
           0 == pseudo(actual, guess, 4);
}

int test_no_hits_all_pseudo() {
    char actual[] = {'R', 'G', 'B', 'Y'};
    char guess[] = {'G', 'B', 'Y', 'R'};
    return 0 == hits(actual, guess, 4) &&
           4 == pseudo(actual, guess, 4);
}

int test_all_hits_no_pseudo() {
    char actual[] = {'R', 'G', 'B', 'Y'};
    char guess[] = {'R', 'G', 'B', 'Y'};
    return 4 == hits(actual, guess, 4) &&
           0 == pseudo(actual, guess, 4);
}

int test_no_hits_pseudo() {
    char actual[] = {'R', 'G', 'G', 'R'};
    char guess[] = {'G', 'R', 'Y', 'Y'};
    return 0 == hits(actual, guess, 4) &&
           2 == pseudo(actual, guess, 4);
}

int test_hits_no_pseudo() {
    char actual[] = {'R', 'G', 'G', 'R'};
    char guess[] = {'Y', 'G', 'Y', 'Y'};
    return 1 == hits(actual, guess, 4) &&
           0 == pseudo(actual, guess, 4);
}

int test_hits_pseudo() {
    char actual[] = {'R', 'G', 'G', 'R'};
    char guess[] = {'Y', 'G', 'R', 'Y'};
    return 1 == hits(actual, guess, 4) &&
           1 == pseudo(actual, guess, 4);
}

int main() {
    int counter = 0;
    if (!test_no_hits_no_pseudo()) {
        printf("No hits, no pseudo test failed!\n");
        counter++;
    }
    if (!test_no_hits_all_pseudo()) {
        printf("No hits, all pseudo test failed!\n");
        counter++;
    }
    if (!test_all_hits_no_pseudo()) {
        printf("All hits, no pseudo test failed!\n");
        counter++;
    }
    if (!test_no_hits_pseudo()) {
        printf("No hits, pseudo test failed!\n");
        counter++;
    }
    if (!test_hits_no_pseudo()) {
        printf("Hits, no pseudo test failed!\n");
        counter++;
    }
    if (!test_hits_pseudo()) {
        printf("Hits, pseudo test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

