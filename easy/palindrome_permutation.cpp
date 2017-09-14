#include <string>
#include <iostream>

// Task description: Given a string, write a function that will check whether
// it is a permutation of a palindrome or not. A palindrome is a word or phrase
// that is spelled the same forwards and backwards. A permutation is a
// rearrangement of letters.
//
// E.g. "nana" is a permutation of "anna", the method should return true
//      "ciciv" is a permutation of "civic", the method should return true
//      "animal" is not a permutation of a palindrome, it should return false
//
// Solution: A given string is a permutation of a palindrome only when the
// count of each letter in the string is even except from one that can be odd.
//
// The first solution is implementing this algorithm by keeping a count of each
// distinct letter in the input string and then checking that all counts are
// even except from one at maximum that can be odd.
//
// The second solution is also implementing the logic above but instead of
// storing the counts for each letter, it is storing a bit that flags whether
// the count is even or odd. With each reoccurance of the same character, the
// bit in the bitVector is flipped. In the end it returns true only if the
// bitVector is zero or has at maximum only one bit set.

bool is_palindrome_permutation(std::string input) {
    int counts[26] = { };
    for (int i = 0; i < input.size(); i++) {
        int index = tolower(input.at(i)) - 'a';
        if (index >= 0 && index < 26) {
            counts[index]++;
        }
    }

    bool foundOdd = false;
    for (int i = 0; i < 26; i++) {
        if (counts[i] % 2 != 0) {
            if (foundOdd) {
                return false;
            }
            foundOdd = true;
        }
    }
    return true;
}

bool is_palindrome_permutation_2(std::string input) {
    int bitVector = 0;
    for (int i = 0; i < input.size(); i++) {
        int index = tolower(input.at(i)) - 'a';
        if (index >= 0 && index < 26) {
            int mask = 1 << index;
            if (bitVector & mask) {
                bitVector &= ~mask;
            } else {
                bitVector |= mask;
            }
        }
    }
    return bitVector == 0 || ((bitVector - 1) & bitVector) == 0;
}

// Palindrome is: anna
bool test_palindrome_permutation_even() {
    return is_palindrome_permutation("nana") &&
           is_palindrome_permutation_2("nana");
}

// Palindrome is: civic
bool test_palindrome_permutation_odd() {
    return is_palindrome_permutation("ciciv") &&
           is_palindrome_permutation_2("ciciv");
}

bool test_not_palindrome_permutation() {
    return !is_palindrome_permutation("animal") &&
           !is_palindrome_permutation_2("animal");
}

int main() {
    int counter = 0;
    if (!test_palindrome_permutation_even()) {
        std::cout << "Even palindrome permutation test failed!" << std::endl;
        counter++;
    }
    if (!test_palindrome_permutation_odd()) {
        std::cout << "Odd palindrome permutation test failed!" << std::endl;
        counter++;
    }
    if (!test_not_palindrome_permutation()) {
        std::cout << "Not palindrome permutation test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

