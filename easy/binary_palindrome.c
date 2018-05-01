#include <stdio.h>

// Task description: Given an integer, write a method to determine whether its
// binary representation forms a palindrome.
//
// E.g. For integer 0xFF0000FF the method should return true
//      For integer 0xFF000000 the method should return false
//
// Solution: The implementation below uses a left and a right pointer to keep
// track of which bit positions to compare in each iteration. It loops through
// all bit positions and returns false as soon as a mismatch has been found.

int palindrome(int num) {
    int left = sizeof(unsigned int) * 8 - 1;
    int right = 0;
    while (left > right) {
        if (((num & (1 << left)) != 0) !=
            ((num & (1 << right)) != 0)) return 0;
        left--;
        right++;
    }
    return 1;
}

int test_palindrome() {
    return palindrome(0x00000000) &&
           palindrome(0xFFFFFFFF) &&
           palindrome(0xF000000F) &&
           palindrome(0xFF0000FF) &&
           palindrome(0xFFF00FFF) &&
           palindrome(0x0FFFFFF0) &&
           palindrome(0x00FFFF00) &&
           palindrome(0x000FF000);
}

int test_not_palindrome() {
    return !palindrome(0x0000000F) &&
           !palindrome(0x000000FF) &&
           !palindrome(0x00000FFF) &&
           !palindrome(0x0000FFFF) &&
           !palindrome(0x000FFFFF) &&
           !palindrome(0x00FFFFFF) &&
           !palindrome(0x0FFFFFFF);
}

int main() {
    int counter = 0;
    if (!test_palindrome()) {
        counter++;
        printf("Palindrome test failed!\n");
    }
    if (!test_not_palindrome()) {
        counter++;
        printf("Not palindrome test failed!\n");
    }
    printf("%d tests failed!\n", counter);
}

