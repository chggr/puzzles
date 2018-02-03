#include <iostream>
#include <string>
#include <vector>

// Task description: Given a very long input string and a much smaller search
// string, identify the instances of the search string in the input string.
// Can this be done in linear time?
//
// E.g. for input string "the quick brown fox jumped over the lazy dog"
//      and search string "the"
//      the method should return [0, 32]
//
// Solution: The first implementation below uses a brute force algorithm to
// search through the input string. For every position in the input string, it
// iterates through the search string trying to find a match. This approach has
// O(1) space complexity because it does not use any additional memory except
// from the vector to hold the results. Its runtime complexity is O(m * (n - m)),
// where m is the length of the search string and n is the length of the input
// string.
//
// The second implementation uses the Rabin-Karp algorithm to optimize searching
// by pre-computing the hash value of each character sequence in the input
// string with length equal to that of the search string. It then compares the
// value of the hash versus that of the search string to locate and return
// matches. The runtime complexity of this approach is O(n) because it needs
// to go through the input string twice: the first time to compute the hashes
// and the second time to identify matches. The space complexity is also O(n),
// for the auxiliary table that stores the hashes.
//
// The hash function used here is simply the sum of the characters, which is
// not optimal and might lead to many false positives. In practice we would use
// a better rolling hash function, such as the Rabin fingerprint. This function
// treats each string as a base 128 number (or however many characters are in
// the alphabet) and computes the hash value as follows:
//
// hash("cat") = code('c') * 128^2 + code('a') * 128 ^ 1 + code('t') * 128^0
// hash("ats") = (hash("cat") - code('c') * 128^2) * 128 + code('s') * 128^0
//
// As shown above, the Rabin fingerprint is a rolling hash function that allows
// us to easily slide the window by one character and compute the new hash
// through simple O(1) calculations. Indeed a rolling hash function is a vital
// requirement for the Rabin-Karp algorithm to work efficiently.

using namespace std;

vector<int> search_brute(string input, string search) {
    vector<int> results;
    if (input.empty() || search.empty()) {
        return results;
    }

    bool match;
    for (int i = 0; i < input.length() - search.length() + 1; i++) {
        match = true;
        for (int j = 0; j < search.length(); j++) {
            if (input[i + j] != search[j]) {
                match = false;
                break;
            }
        }
        if (match) results.push_back(i);
    }
    return results;
}

vector<int> hash(string input, int length) {
    vector<int> hashes;

    // Compute the hash for the first element.
    int hash = 0;
    for (int i = 0; i < length; i++) {
        hash += input[i];
    }
    hashes.push_back(hash);

    // Use sliding window to compute remaining hashes.
    for (int i = 1; i < input.length() - length + 1; i++) {
        hash -= input[i - 1];
        hash += input[i + length - 1];
        hashes.push_back(hash);
    }
    return hashes;
}

int hash(string input) {
    int hash = 0;
    for (int i = 0; i < input.length(); i++) {
        hash += input[i];
    }
    return hash;
}

vector<int> search(string input, string search) {
    vector<int> results;
    if (input.empty() || search.empty()) {
        return results;
    }

    // Compute hashes for input and search string.
    vector<int> hashes = hash(input, search.length());
    int search_hash = hash(search);

    // Identify and verify possible matches.
    for (int i = 0; i < hashes.size(); i++) {
        if (hashes.at(i) != search_hash) continue;

        bool match = true;
        for (int j = 0; j < search.length(); j++) {
            if (input[i + j] != search[j]) {
                match = false;
                break;
            }
        }
        if (match) results.push_back(i);
    }
    return results;
}

static const string INPUT = "the quick brown fox jumped over the lazy dog";

bool test_input_empty() {
    vector<int> results_brute = search_brute("", "fox");
    vector<int> results = search("", "fox");
    return results_brute.empty() && results.empty();
}

bool test_search_empty() {
    vector<int> results_brute = search_brute(INPUT, "");
    vector<int> results = search(INPUT, "");
    return results_brute.empty() && results.empty();
}

bool test_no_matches() {
    vector<int> results_brute = search_brute(INPUT, "blue");
    vector<int> results = search(INPUT, "blue");
    return results_brute.empty() && results.empty();
}

bool test_one_match() {
    vector<int> results_brute = search_brute(INPUT, "dog");
    vector<int> results = search(INPUT, "dog");
    return 1 == results_brute.size() && 41 == results_brute.at(0) &&
           1 == results.size() && 41 == results.at(0);
}

bool test_two_matches() {
    vector<int> results_brute = search_brute(INPUT, "the");
    vector<int> results = search(INPUT, "the");
    return 2 == results_brute.size() &&
           0 == results_brute.at(0) &&
           32 == results_brute.at(1) &&
           2 == results.size() &&
           0 == results.at(0) &&
           32 == results.at(1);
}

int main() {
    int counter = 0;
    if (!test_input_empty()) {
        cout << "Empty input test failed!" << endl;
        counter++;
    }
    if (!test_search_empty()) {
        cout << "Empty search test failed!" << endl;
        counter++;
    }
    if (!test_no_matches()) {
        cout << "No matches test failed!" << endl;
        counter++;
    }
    if (!test_one_match()) {
        cout << "One match test failed!" << endl;
        counter++;
    }
    if (!test_two_matches()) {
        cout << "Two matches test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

