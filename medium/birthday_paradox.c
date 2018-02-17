#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Task description: Given N randomly chosen people, write a method to calculate
// the probability that two or more of them will share the same birthday.
//
// Solution: The probability will be 100% if N is equal or greater to 365, since
// there are 365 possible birthdays. The paradox is that 99.9% is reached with
// just 70 people and 50% with just 23 people. These calculations are based on
// the assumption that each day of the year is equally probable for a birthday.
//
// The first implementation below uses the Monte Carlo technique to estimate the
// probability that two or more people with share the same birthday. It conducts
// an experiment where N birthdays are randomly chosen and we check if two of
// them are the same. This experiment is repeated many times to estimate the
// probability of that happening. The runtime complexity of this approach is
// O(R*N) where R is the number or experiments executed and N the number of
// people.
//
// The second implementation first calculates the probability that no people
// share the same birthday as follows: 365/365 * 364/365 * 363/365 and so on.
// That's because having chosen one birthday, the probability of the second
// birthday not being the same is 364/365. Furthermore, having chosen two
// birthdays the probability of the third not being the same is 363/365 and
// so on. The requested probability will be the one minus the one we have
// calculated. The runtime complexity of this approach is O(1).

// Runs an experiment with the given number of people and returns
// whether at least two of them share the same birthday.
int same_birthday(int people) {
    int year[365] = {0};

    for (int i = 0; i < people; i++) {
        year[rand() % 365]++;
    }
    for (int i = 0; i < 365; i++) {
        if (year[i] > 1) return 1;
    }
    return 0;
}

double probability_mc(int people, int experiments) {
    int count = 0;
    for (int i = 0; i < experiments; i++) {
        count += same_birthday(people);
    }
    return (1.0 * count) / experiments;
}

double probability(int people) {
    double result = 1.0;
    for (int i = 0; i < people; i++) {
        result *= (365.0 - i) / 365.0;
    }
    return 1.0 - result;
}

double round(double value) {
    int temp = value * 100;
    return temp / 100.0;
}

int test_10() {
    return 0.11 == round(probability(10)) &&
           0.11 == round(probability_mc(10, 100000));
}

int test_23() {
    return 0.50 == round(probability(23)) &&
           0.50 == round(probability_mc(23, 100000));
}

int test_70() {
    return 0.99 == round(probability(70)) &&
           0.99 == round(probability_mc(70, 100000));
}

int main() {
    srand(time(NULL));
    int counter = 0;
    if (!test_10()) {
        printf("Probability with 10 people test failed!\n");
        counter++;
    }
    if (!test_23()) {
        printf("Probability with 23 people test failed!\n");
        counter++;
    }
    if (!test_70()) {
        printf("Probability with 70 people test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

