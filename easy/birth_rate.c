#include <stdio.h>
#include <stdlib.h>

// Task description: In a distant country the authorities are desperately
// concerned about the birth rate and they have decided that all families by
// law need to have at least one girl or face huge fines. Let's assume that
// all families abide to this policy and continue having children until they
// have one girl, at which point they stop having any more children. What will
// be the gender ratio of the new generation, assuming that the chances of
// having a boy or a girl in each pregnancy are equal? Solve this logically and
// also write a program to simulate the result.
//
// Solution: Each family will have a sequence of zero or more boys followed by
// a single girl (i.e. G, BG, BBG, BBBG, BBBBG and so on), with the probability
// of each combination begin 1/2, 1/4, 1/8, 1/16, 1/32, etc. In every case there
// will be at least one girl and the number of boys would be 1/2 * 0 + 1/4 * 1 +
// 1/8 * 2 + 1/16 * 3 + 1/32 * 4, etc. This sequence sums up to one, and thus
// the ration between boys and girls in the new generation will be 50-50.
//
// The simulation below arrives to the same result. Method is_girl() returns
// whether a child is boy or girl with probability 50% each. Method
// get_children() returns how many children a random family might have: at least
// one child and possibly more until there is a girl. Finally method simulate()
// calculates the ratio between boys and girls for a given number number of
// families. As the number of families grows, this ratio gets closer and closer
// to 1, meaning even distribution between boys and girls.

int is_girl() {
    return (rand() % 100) < 50;
}

int get_children() {
    int children = 1;
    while (!is_girl()) {
        children++;
    }
    return children;
}

double simulate(int runs) {
    int boys = 0;
    int girls = 0;

    for (int i = 0; i < runs; i++) {
        girls++;
        boys += get_children() - 1;
    }
    return (1.0 * boys) / girls;
}

int test_simulate() {
    return abs(simulate(1000) - 1.0) < 0.001;
}

int main() {
    if (!test_simulate()) {
        printf("Simulation failed!\n");
    } else {
        printf("Simulation successful.\n");
    }
}

