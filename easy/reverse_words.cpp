#include <iostream>
#include <string>

// Task description: Write a method to reverse the order of the words in an
// input string. All words are space delimited and the operation should be
// performed in place.
//
// E.g. for input string "lorem ipsum dolor sit amet"
//      the method should return "amet sit dolor ipsum lorem"
//
// Solution: An obvious approach would be to use a scanner to scan the input
// string from right to left and copy a word in a temporary buffer as soon as it
// reaches a space character or the first character. Then copy the contents of
// the temporary buffer back into the input string. The runtime complexity of
// this approach is O(n) and space complexity is also O(n) because additional
// space is required for the temporary buffer.
//
// The implementation below initially reverses the whole input string in place
// and then goes through the string and reverses each word separately. For
// example, input string "lorem ipsum dolor sit amet" becomes "tema tis rolod
// muspi merol" after the first operation and then "amet sit dolor ipsum lorem"
// after the second operation. Both operations happen in place and thus the
// space complexity is O(1). Runtime complexity is O(n).

// Reverses the input string between its start and end indexes inclusive.
void reverse(std::string &input, int start, int end) {
    if (start < 0 || end >= input.size()) return;

    int length = end - start;
    for (int i = 0; i <= length / 2; i++) {
        char temp = input[start + i];
        input[start + i] = input[end - i];
        input[end - i] = temp;
    }
}

// Reverses all words in the given sentence.
void reverse(std::string &input) {
    reverse(input, 0, input.size() - 1);

    int start = 0;
    int end = 0;
    for (int i = 0; i <= input.size(); i++) {
        if (input[i] == ' ' || input[i] == '\0') {
            end = i - 1;
            reverse(input, start, end);
            start = i + 1;
        }
    }
}

bool test_reverse_invalid_start() {
    std::string s = "lorem ipsum dolor sit amet";
    reverse(s, -1, s.size());
    return s == "lorem ipsum dolor sit amet";
}

bool test_reverse_invalid_end() {
    std::string s = "lorem ipsum dolor sit amet";
    reverse(s, 0, s.size());
    return s == "lorem ipsum dolor sit amet";
}

bool test_reverse_middle() {
    std::string s = "lorem ipsum dolor sit amet";
    reverse(s, 6, 10);
    return s == "lorem muspi dolor sit amet";
}

bool test_reverse_whole() {
    std::string s = "lorem ipsum dolor sit amet";
    reverse(s, 0, s.size() - 1);
    return s == "tema tis rolod muspi merol";
}

bool test_reverse_sentence() {
    std::string s = "lorem ipsum dolor sit amet";
    reverse(s);
    return s == "amet sit dolor ipsum lorem";
}

int main() {
    int counter = 0;
    if (!test_reverse_invalid_start()) {
        std::cout << "Invalid start reverse test failed!" << std::endl;
        counter++;
    }
    if (!test_reverse_invalid_end()) {
        std::cout << "Invalid end reverse test failed!" << std::endl;
        counter++;
    }
    if (!test_reverse_middle()) {
        std::cout << "Middle reverse test failed!" << std::endl;
        counter++;
    }
    if (!test_reverse_whole()) {
        std::cout << "Whole reverse test failed!" << std::endl;
        counter++;
    }
    if (!test_reverse_sentence()) {
        std::cout << "Sentence reverse test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

