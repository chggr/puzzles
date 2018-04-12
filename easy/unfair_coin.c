#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task description: Given a method that represents an unfair coin and returns
// true with 40% probability and false with 60% probability, write a second
// method to represent a fair coin that returns true or false with 50%
// probability. Your method should not use any libraries, just the unfair coin.
//
// Solution: The unfair coin can still be used to generate fair results by using
// the following procedure first described by John von Neumann:
//
// (1) Toss the coin twice.
// (2) If the results match, discard them and start again
// (3) If the results do not match, use the first result.
//
// The explanation of why this works becomes apparent when we analyze the truth
// table using the unfair coin in this puzzle. As seen below, the probability of
// getting true / false and false / true is exactly the same. By excluding the
// true / true and false / false events, the coin flipping is left with only the
// two remaining outcomes that are of equal probability. Note that this process
// only works if the tosses are paired and discarded properly. If part of a pair
// is reused in another pair, the fairness is ruined.
//
//  TOSS A     TOSS B      PROBABILITY
//  true       true        0.4 * 0.4 = 0.16
//  false      false       0.6 * 0.6 = 0.36
//  true       false       0.4 * 0.6 = 0.24
//  false      true        0.6 * 0.4 = 0.24

// Unfair coin, returns false with 60% and true with 40% probability,
int unfair() {
    return rand() % 10 > 5;
}

// Fair coin, 50% probability for true or false.
int fair() {
    while(1) {
        int toss1 = unfair();
        int toss2 = unfair();
        if (toss1 != toss2) return toss1;
    }
}

int test_unfair() {
    double heads = 0;
    double tails = 0;

    for (int i = 0; i < 1000000; i++) {
        if (unfair()) heads++;
        else tails++;
    }
    heads /= 1000000;
    tails /= 1000000;

    return fabs(heads - 0.4) < 0.01 &&
           fabs(tails - 0.6) < 0.01;
}

int test_fair() {
    double heads = 0;
    double tails = 0;

    for (int i = 0; i < 1000000; i++) {
        if (fair()) heads++;
        else tails++;
    }
    heads /= 1000000;
    tails /= 1000000;

    return fabs(heads - 0.5) < 0.01 &&
           fabs(tails - 0.5) < 0.01;
}

int main() {
    srand(time(0));
    int counter = 0;
    if (!test_unfair()) {
        counter++;
        printf("Unfair coin test failed.\n");
    }
    if (!test_fair()) {
        counter++;
        printf("Fair coin test failed.\n");
    }
    printf("%d tests failed.\n", counter);
}

