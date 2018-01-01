#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task description: Given a function rand5() that returns random numbers
// between 0 and 4, write a function rand7() that will return random numbers
// between 0 and 6.
//
// Solution: To solve this task correctly, method rand7() should return values
// 0 to 6 with probability equal to 1/7 each. As a first attempt we might try
// calling rand5() twice and return the sum of the results modulo 7. I.e.
// (rand5() + rand5()) % 7. This is not correct unfortunately, as there are
// some values that appear more frequently than others. For example value 0
// appears three times: (0,0) (3,4) (4,3) but value 4 appears five times: (0,4)
// (4,0) (3,1) (1,3) (2,2). Thus this method is not correct because the
// probability of four is much higher than the probability of zero.
//
// In the implementation below we generate the range 0 through 24 by using
// function 5 * rand5() + rand5(). This function guarantees that each number
// between 0 and 24 has the same probability of appearing. Values greater or
// equal to 21 need to be discarded so that the final result after taking mod
// by 7 is not skewed.

int rand5() {
    return rand() % 5;
}

int rand7() {
    for (;;) {
        int res = 5 * rand5() + rand5();
        if (res < 21) return res % 7;
    }
}

int test_rand5() {
    int counter[5] = { 0 };
    for (int i = 0; i < 5000000; i++) {
        counter[rand5()]++;
    }

    for (int i = 0; i < 5; i++) {
        double error = (counter[i] - 1000000) / 1000000.0;
        if (error > 0.01) return 0;
    }
    return 1;
}

int test_rand7() {
    int counter[7] = { 0 };
    for (int i = 0; i < 7000000; i++) {
        counter[rand7()]++;
    }

    for (int i = 0; i < 7; i++) {
        double error = (counter[i] - 1000000) / 1000000.0;
        if (error > 0.01) return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));

    int counter = 0;
    if (!test_rand5()) {
        printf("Rand5 test failed!\n");
        counter++;
    }
    if (!test_rand7()) {
        printf("Rand7 test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

