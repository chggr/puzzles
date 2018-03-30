#include <iostream>
#include <string>
#include <vector>

// Task description: Given a string of text and a pattern, write a method to
// return all positions in the text where the pattern occurs.
//
// Solution: A naive brute force solution would be to go through each position
// in the given text and search for the pattern. The runtime complexity of this
// approach is O(T*P) where T is the number of characters in the text and P is
// the number of characters in the pattern. This is the worst-case complexity,
// but in many situations it is not as bad as it looks. That's because the inner
// loop usually finds a mismatch quickly and moves on to the next position
// without going through all P steps. For example if we are searching for a word
// in english text, the probability of the next position matching at random is
// just 1/26. This is quite low and it gets lower as we continue searching for
// subsequent characters. Nevertheless there are inputs where this simple
// algorithm is not adequate.
//
// The solution below is an implementation of the Knuth-Morris-Pratt string
// matching algorithm. It starts by preprocessing the pattern to create the
// prefix table, which at each position indicates how many skips we can make
// when coming across a mismatch. It then searches through the text as follows:
// A text index and a pattern index are maintained and incremented when the
// characters match. If the pattern index reaches the end of the pattern, then
// a full match has been found and the pattern index is reset according to the
// prefix table. On the contrary, if the characters do not match then we take
// action according to the value of the pattern index. If it is zero, it means
// that no portion of the pattern has matched and thus we need to increment the
// text index. If it is not zero, then some portion of the pattern has matched
// and thus the pattern index can be reset according to the prefix table. The
// runtime complexity of this algorithm is O(T + P) where T is the number of
// characters in the text and P is the number of characters in the pattern.
// Computing the prefix table takes O(P) and searching through the text takes
// O(T), giving a combined O(T + P).

using namespace std;

// Creates the prefix table for the given pattern. The first position is always
// set to zero. We then populate all subsequent positions by keeping track of
// the longest suffix found until now (variable len) and comparing the character
// at the current position with the character at position len from the beginning
// of the pattern. If they are the same, we can extend the longest suffix. If
// they are different, we need to reduce len and recalculate for the current
// position until either len reaches zero or we have found a match.
int* prefix(string pattern) {
    int* P = new int[pattern.length()];
    P[0] = 0;

    int len = 0; // length of previous longest suffix.
    for (int i = 1; i < pattern.length(); i++) {
        if (pattern[i] == pattern[len]) {
            len++;
            P[i] = len;
        } else {
            if (len == 0) {
                P[i] = len;
            } else {
                len = P[len - 1];
                i--;
            }
        }
    }
    return P;
}

vector<int> search(string text, string pattern) {
    int* prefix_table = prefix(pattern);

    vector<int> result;
    int t_idx = 0;
    int p_idx = 0;

    while (t_idx < text.length()) {

        // If characters match, increment both indices.
        if (text[t_idx] == pattern[p_idx]) {
            t_idx++;
            p_idx++;
        }

        // Match has been found.
        if (p_idx == pattern.length()) {
            result.push_back(t_idx - p_idx);
            p_idx = prefix_table[p_idx - 1];
            continue;
        }

        // Characters do not match.
        if (text[t_idx] != pattern[p_idx]) {
            if (p_idx == 0) t_idx++;
            else p_idx = prefix_table[p_idx - 1];
        }
    }

    delete prefix_table;
    return result;
}

bool equal(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool test_prefix_all_same() {
    int expected[] = {0, 1, 2, 3, 4};
    return equal(prefix("AAAAA"), expected, 5);
}

bool test_prefix_all_different() {
    int expected[] = {0, 0, 0, 0, 0};
    return equal(prefix("ABCDE"), expected, 5);
}

bool test_prefix() {
    int expected[] = {0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5};
    return equal(prefix("AABAACAABAA"), expected, 11);
}

bool test_prefix_repeating() {
    int expected[] = {0, 1, 2, 0, 1, 2, 3, 3, 3, 4};
    return equal(prefix("AAACAAAAAC"), expected, 10);
}

bool test_find_no_match() {
    vector<int> result = search("AAAAABAAABA", "ABC");
    return 0 == result.size();
}

bool test_find_one_match() {
    vector<int> result = search("AAAAABAAABCA", "ABC");
    return 1 == result.size() && 8 == result.at(0);
}

bool test_find_two_matches() {
    vector<int> result = search("AAAAABAAABA", "AB");
    return 2 == result.size() && 4 == result.at(0) && 8 == result.at(1);
}

bool test_find_many_matches() {
    vector<int> result = search("AAAAABAAABA", "AAA");
    return 4 == result.size() && 0 == result.at(0) && 1 == result.at(1) &&
           2 == result.at(2) && 6 == result.at(3);
}

int main() {
    int counter = 0;
    if (!test_prefix_all_same()) {
        counter++;
        cout << "All letters same prefix test failed!" << endl;
    }
    if (!test_prefix_all_different()) {
        counter++;
        cout << "All letters different prefix test failed!" << endl;
    }
    if (!test_prefix()) {
        counter++;
        cout << "Prefix test failed!" << endl;
    }
    if (!test_prefix_repeating()) {
        counter++;
        cout << "Repeating prefix test failed!" << endl;
    }
    if (!test_find_no_match()) {
        counter++;
        cout << "No match find test failed!" << endl;
    }
    if (!test_find_one_match()) {
        counter++;
        cout << "One match find test failed!" << endl;
    }
    if (!test_find_two_matches()) {
        counter++;
        cout << "Two matches find test failed!" << endl;
    }
    if (!test_find_many_matches()) {
        counter++;
        cout << "Many matches find test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

