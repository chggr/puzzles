#include <stdio.h>
#include <string.h>

// Task description: Write methods atoi() and itoa() to convert an integer to
// string and a string to integer respectively.
//
// e.g. atoi("-1234") should return integer -1234
//      itoi(-1234) should return string "-1234"
//
// Solution: The implementation of atoi() below first detects whether the input
// string contains a sign (- or +) and then goes through the rest of the string
// calculating the integer. It returns the signed result. The space complexity
// is O(1) and runtime complexity is O(n), where n is the length of the input
// string.
//
// itoa() is implemented in a similar fashion. It first extracts the sign and
// then goes through the given integer from right to left, storing each digit in
// the output array. Finally the output array is reversed before return. The
// space complexity of itoa() is O(1) because all operations happen in place.
// The runtime complexity is O(n).

// Converts a string into integer.
int atoi(char *input) {
    if (input == NULL) return 0;

    // Extract the sign.
    int i = 0;
    int sign = 1;
    if (input[0] == '-' || input[0] == '+') {
        sign = input[0] == '-' ? -1 : 1;
        i++;
    }

    // Extract the number
    int result = 0;
    int digit;
    while (input[i] != '\0') {
        digit = input[i] - '0';
        if (digit < 0 || digit > 9) return 0;

        result *= 10;
        result += digit;
        i++;
    }

    return sign * result;
}

// Reverses a char array.
void reverse(char* array, int size) {
    if (size <= 1) return;

    for (int i = 0; i < size / 2; i++) {
        int temp = array[i];
        array[i] = array[size - i];
        array[size - i] = temp;
    }
}

// Converts an integer into string.
void itoa(int input, char* output) {
    if (output == NULL) return;

    // Extract the sign.
    char sign = ' ';
    if (input < 0) {
        sign = '-';
        input = -input;
    }

    // Extract the number;
    int idx = 0;
    int digit;
    do {
        digit = input % 10;
        input /= 10;
        output[idx] = '0' + digit;
        idx++;
    } while (input != 0);
    output[idx] = sign;

    reverse(output, idx);
    output[idx + 1] = '\0';
}

int test_atoi() {
    return 0 == atoi(0) &&
           0 == atoi("") &&
           0 == atoi("test") &&
           0 == atoi("0") &&
           12345 == atoi("12345") &&
           12345 == atoi("+12345") &&
           -12345 == atoi("-12345");
}

int test_itoa() {
    char output[10];
    int result = 1;

    itoa(0, output);
    result = result && strcmp("0", output);

    itoa(1234, output);
    result = result && strcmp("1234", output);

    itoa(-1234, output);
    result = result && strcmp("-1234", output);

    return result;
}

int main () {
    int counter = 0;
    if (!test_atoi) {
        printf("Atoi test failed!\n");
        counter++;
    }
    if (!test_itoa) {
        printf("Itoa test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

