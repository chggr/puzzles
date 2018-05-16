#include <iostream>

// Task description: Given a string, find its rank among all of its permutations
// sorted lexicographically.
//
// For example, rank of "ABC" is 0 and rank of "CAB" is 4.
//
// Solution: A brute force solution would be to generate all permutation of the
// string in lexicographical order and return the rank once we have encountered
// the given string. The runtime complexity of this approach is O(N!).
//
// The implementation below uses a better approach to directly calculate the
// rank of the given string. For each position, it goes through the remaining
// characters in the string and counts how many are less than the current
// character. These characters should normally appear before the current one and
// therefore contribute to its rank by the factorial of the count of remaining
// characters. This approach uses two loops and therefore the runtime complexity
// is O(N^2).

using namespace std;

// Calculates the factorial of a number.
int factorial(int num) {
    int result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

int getRank(string s) {
    int result = 0;
    for (int i = 0; i < s.length(); i++) {

        // Find all characters on the right that are smaller.
        int smaller = 0;
        for (int j = i + 1; j < s.length(); j++) {
            if (s[i] > s[j]) smaller++;
        }
        result += smaller * factorial(s.length() - 1 - i);
    }
    return result;
}

bool testEmpty() {
    return 0 == getRank("");
}

bool testSorted() {
    return 0 == getRank("ABC") && 0 == getRank("DEFGHI");
}

bool testUnsorted() {
    return 4 == getRank("CAB") &&  2 == getRank("BAC") &&
           597 == getRank("STRING");
}

int main() {
    int counter = 0;
    if (!testEmpty()) {
        counter++;
        cout << "Empty test failed!" << endl;
    }
    if (!testSorted()) {
        counter++;
        cout << "Sorted test failed!" << endl;
    }
    if (!testUnsorted()) {
        counter++;
        cout << "Unsorted test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

