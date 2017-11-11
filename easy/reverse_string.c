#include <stdio.h>

// Task description: Implement a function in C to reverse a null terminated
// string.
//
// Solution: There are multiple ways to solve this task. In the implementation
// below we first calculate the length of the input string and then loop from
// the beginning up to the middle of the string, swapping elements from the
// lower and higher halves. An alternative approach would be to use pointer
// arithmetic. The runtime complexity of both approaches is O(n).

void reverse(char* input) {
    int len = 0;
    while(input[len]) {
        len++;
    }

    char tmp;
    for (int i = 0; i < len / 2; i++) {
        tmp = input[i];
        input[i] = input[len - 1 - i];
        input[len - 1 - i] = tmp;
    }
}

int equal(char* a, char* b) {
    int tmp = 0;
    while (a[tmp] && b[tmp]) {
        if (a[tmp] != b[tmp]) return 0;
        tmp++;
    }
    return !a[tmp] && !b[tmp];
}

int test_equal() {
    return !equal("", "abc") &&
           !equal("abc", "") &&
           equal("", "") &&
           equal("abc", "abc") &&
           !equal("abc", "abcd") &&
           !equal("abcd", "abc") &&
           equal("abcd", "abcd");
}

int test_reverse_empty() {
    char string[] = "";
    reverse(string);
    return equal("", string);
}

int test_reverse_single_char() {
    char string[] = "a";
    reverse(string);
    return equal("a", string);
}

int test_reverse_odd_chars() {
    char string[] = "abc";
    reverse(string);
    return equal("cba", string);
}

int test_reverse_even_chars() {
    char string[] = "abcd";
    reverse(string);
    return equal("dcba", string);
}

int main() {
    int counter = 0;
    if (!test_equal()) {
        printf("String equality test failed!\n");
        counter++;
    }
    if (!test_reverse_empty()) {
        printf("Reverse empty string test failed!\n");
        counter++;
    }
    if (!test_reverse_single_char()) {
        printf("Reverse single character string test failed!\n");
        counter++;
    }
    if (!test_reverse_odd_chars()) {
        printf("Reverse odd characters string test failed!\n");
        counter++;
    }
    if (!test_reverse_even_chars()) {
        printf("Reverse even characters string test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

