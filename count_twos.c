#include <math.h>
#include <stdio.h>

// Task description: Given a positive integer n, write a method to count the
// number of twos between 0 and n inclusive.
//
// E.g. for n = 1 the answer is 0
//      for n = 11 the answer is 1 (2)
//      for n = 22 the answer is 6 (2, 12, 20, 21, 22)
//
// Solution: The first implementation below uses a brute force approach to solve
// this task. For every number between 0 and n, it extracts its digits and
// increments a counter if any one of them is equal to two. It finally returns
// the result. The runtime complexity of this implementation is O(N*M) where N
// is the given number and M is the average number length. This method runs fast
// for small inputs, but its performance is very bad for larger inputs.
//
// The second implementation greatly improves the runtime complexity by using
// numerical analysis to calculate the final result in O(M), where M is the
// number of digits in the input number. It goes through each digit one by one
// and extracts the numbers at the left and right of this digit. For example
// number 43210 and digit 2, the left and right will be 43 and 10 respectively.
// It subsequently increments the result according to the following analysis:
//
// - If the digit is less than two, the total number of twos at that position
//   will be equal to the left times ten to the power of the current position.
//   For example, the number of twos at the third position of number 31523 will
//   be 3000, i.e. ranges 2000 - 2999, 12000 - 12999 and 22000 - 22999.
//
// - If the digit is greater than two, the total number of twos at that position
//   will be equal to the left plus one, times ten to the power of the current
//   position. For example, the number of twos at the third position of number
//   33523 will be 4000, i.e. ranges 2000 - 2999, 12000 - 12999, 22000 - 22999
//   and 32000 - 32999.
//
// - If the digit is equal to two, the total number of twos at that position
//   will be equal to the left times ten to the power of the current position,
//   plus the right plus one. For example, the number of twos at the third
//   position of number 32523 will be 3000 + 524, i.e. ranges 2000 - 2999, 12000
//   - 12999, 22000 - 22999 and 32000 - 32523.

int count_twos_brute(int num) {
    int current;
    int result = 0;
    for (int i = 2; i <= num; i++) {
        current = i;
        while (current > 0) {
            result += current % 10 == 2;
            current /= 10;
        }
    }
    return result;
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int count_twos(int num) {
    int result = 0;
    int pos = 0;
    int temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        int left = num / power(10, pos + 1);
        int right = num % power(10, pos);

        if (digit < 2) {
            result += left * power(10, pos);
        } else if (digit > 2) {
            result += (left + 1) * power(10, pos);
        } else {
            result += left * power(10, pos) + right + 1;
        }

        temp /= 10;
        pos++;
    }
    return result;
}

int test_no_twos() {
    return 0 == count_twos_brute(0) &&
           0 == count_twos(0) &&
           0 == count_twos_brute(1) &&
           0 == count_twos(1);
}

int test_with_twos() {
    return 1 == count_twos_brute(11) &&
           1 == count_twos(11) &&
           2 == count_twos_brute(19) &&
           2 == count_twos(19) &&
           6 == count_twos_brute(22) &&
           6 == count_twos(22) &&
           175 == count_twos_brute(342) &&
           175 == count_twos(342);
}

int test_large_numbers() {
    for (int i = 0; i < 10000; i++) {
        if (count_twos_brute(i) != count_twos(i)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int counter = 0;
    if (!test_no_twos()) {
        printf("No twos test failed!\n");
        counter++;
    }
    if (!test_with_twos()) {
        printf("With twos test failed!\n");
        counter++;
    }
    if (!test_large_numbers()) {
        printf("Large numbers test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

