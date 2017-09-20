#include <stdio.h>

// Task description: Given a real number between 0 and 1 (e.g. 0.245), write a
// method to print its binary representation to the standard output. The method
// should print an error if the number cannot be represented accurtely in
// binary with at most 32 bits.
//
// E.g. For input 0.125, the method should print "0.001"
//      For input 0.1, the method should print "Overflow error"

void to_binary(double input) {

    if (input < 0 || input >= 1) {
        printf("Unsupported input.");
    }

    printf("0.");
    double frac = 1.0;
    for (int i = 0; i < 32; i++) {
        if (input == 0) break;

        frac /= 2;
        if (input >= frac) {
            input -= frac;
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");

    if (input > 0) printf("Overflow error\n");
}

int main() {
    to_binary(0.125);
    to_binary(0.1);
}

