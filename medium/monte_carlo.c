#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Task description: Use Monte Carlo simulation to approximate the value of pi.
//
// Solution: In Monte Carlo simulations a system is fed with random inputs and
// the outputs are used to analyze its behaviour. Probability distributions are
// assigned to some or all of the inputs and the probability distribution of the
// outputs are analyzed to better understand the systems behaviour. This is not
// an exact method but a heuristic one.
//
// In the example below, we are using a Monte Carlo simulation to approximate
// the value of pi. A random point is generated where both x and y are between
// 0 and 1. The probability that the point falls inside the circle with center
// (0,0) and radius one is pi / 4. We can therefore calculate this probability
// and derive an estimate for pi by multiplying it by four. The accuracy of the
// estimate depends on how many random simulations have been executed.

// Generates a random number between 0 and 1.
double generate() {
    return (1.0 * rand()) / RAND_MAX;
}

// Runs the given number of simulations to estimate pi.
double pi(long count) {
    long inside = 0;
    long outside = 0;
    double x, y;

    for (long i = 0; i < count; i++) {
        x = generate();
        y = generate();
        if (x * x + y * y <= 1) inside++;
        else outside++;
    }
    return (4.0 * inside) / (inside + outside);
}

int test_pi() {
    return 0.1 > fabs(M_PI - pi(1000000)) &&
           0.01 > fabs(M_PI - pi(10000000)) &&
           0.001 > fabs(M_PI - pi(100000000));;
}

int main() {
    srand(time(NULL));
    int counter = 0;
    if (!test_pi()) {
        printf("Pi test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

