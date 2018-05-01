#include <math.h>
#include <stdio.h>

// Task description: Given a positive integer, write a method to return the
// total number of set bits in the binary representation of all numbers up to
// that integer.
//
// E.g. for 3 the method should return 4 (0b00 / 0b01 / 0b10 / 0b11)
//
// Solution: A simple approach would be to go through all numbers from one up to
// the given integer and for each number count the set bits in its binary form.
// The runtime complexity of this approach would be O(n), because counting the
// bits in a given integer is O(1) but we will have to repeat this n times.
//
// The implementation below is much more efficient and takes advantage of the
// repetitive patterns in the binary representation of numbers. Taking a look at
// the table below, we can derive the following rules:
//
// (1) The binary representation of the first eight numbers is exactly the same
//     as the last eight numbers except from the most significant bit. Therefore
//     we can calculate F(12) for example as F(7) + F(12 - 8) + (12 - 7) = 12 +
//     F(4) + 4 = 12 + 5 + 5 = 22
//
// (2) If the given number is a power of 2, (e.g. 8), then we can easily calculate
//     F(n - 1) by observing that the first bit is set exactly n/2 times, the
//     second bit also n/2 times, etc. Therefore F(n - 1) = F(2^x - 1) = x * n/2
//     = x * 2^x / 2 = x * 2^(x - 1)
//
// (3) Therefore to calculate the number of bits of all numbers from 0 to n, we
//     first need to calculate x = floor(log(n)) and then F(n) = x * 2^(x - 1) +
//     F(n - 2^x) + (n - 2^x + 1)
//
//     NUMBER     BINARY     BIT_COUNT     TOTAL_COUNT
//     1          0001       1             1
//     2          0010       1             2
//     3          0011       2             4
//     4          0100       1             5
//     5          0101       2             7
//     6          0110       2             9
//     7          0111       3             12
//     8          1000       1             13
//     9          1001       2             15
//     10         1010       2             17
//     11         1011       3             20
//     12         1100       2             22
//     13         1101       3             25
//     14         1110       3             28
//     15         1111       4             32
//
// The implementation below applies the aforementioned equation to recursively
// calculate the result. Each recursive call is basically removing the most
// significant bit and therefore the overal runtime complexity is O(logn).

double log2(double num) {
    return log(num) / log(2);
}

int bit_count(int num) {
    if (num <= 1) return num;

    int x = floor(log2(num));
    return x * pow(2, x - 1) +
           bit_count(num - pow(2, x)) +
           num + 1 - pow(2, x);
}

int test_count() {
    return 0 == bit_count(0) &&
           1 == bit_count(1) &&
           2 == bit_count(2) &&
           4 == bit_count(3) &&
           5 == bit_count(4) &&
           7 == bit_count(5) &&
           9 == bit_count(6) &&
           12 == bit_count(7) &&
           13 == bit_count(8) &&
           15 == bit_count(9) &&
           17 == bit_count(10) &&
           20 == bit_count(11) &&
           22 == bit_count(12) &&
           25 == bit_count(13) &&
           28 == bit_count(14) &&
           32 == bit_count(15);
}

int main() {
    int counter = 0;
    if (!test_count()) {
        counter++;
        printf("Count test failed!\n");
    }
    printf("%d tests failed!\n", counter);
}

