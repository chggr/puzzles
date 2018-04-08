#include <iostream>
#include <string>

// Task description: Given two strings, find the length of the longest
// subsequence present in both of them. A subsequence is a sequence that
// appears in the same relative order but is not necessarily continuous.
//
// E.g. for strings "ABCD" and "EADF"
//      the method should return 2 ("AD").
//
// Solution: A naive brute force approach would be to generate all possible
// subsequences for both strings and compare them. If the length of the first
// string is N and the length of the second string is M, the runtime complexity
// of this approach would be O(2^N + 2^M), which is not acceptable for large
// strings.
//
// The first implementation below is recursive: it starts at the beginning of
// each string and checks whether the characters at each position match. If they
// do, then increment both string indices. If not, then increment either one and
// pick the maximum result. The runtime complexity of this approach is again
// exponential and therefore not acceptable.
//
// The second implementation uses a dynamic programming technique to build the
// final solution from the ground up. It creates an MxN memoization matrix that
// will be used to store the solutions to intermediate subproblems. It then
// fills the matrix from the bottom up, using similar logic to the recursive
// implementation but reusing previous results. The runtime complexity of this
// approach is O(N * M) which is much better than before. The space complexity
// is also O(N * M) for the memoization array.

using namespace std;

int lcs_rec(string a, int idx_a, string b, int idx_b) {
    if (idx_a >= a.length() ||
        idx_b >= b.length()) return 0;

    if (a[idx_a] == b[idx_b]) {
        return 1 + lcs_rec(a, idx_a + 1, b, idx_b + 1);
    }
    return max(lcs_rec(a, idx_a + 1, b, idx_b),
               lcs_rec(a, idx_a, b, idx_b + 1));
}

int lcs_dyn(string a, string b) {
    int memo[a.length()][b.length()];
    for (int i = 0; i < a.length(); i++) {
        for (int j = 0; j < b.length(); j++) {
            if (a[i] == b[j]) {
                memo[i][j] = 1 + (i > 0 && j > 0 ? memo[i - 1][j - 1] : 0);
            } else {
                memo[i][j] = max(i > 0 ? memo[i - 1][j] : 0,
                                 j > 0 ? memo[i][j - 1] : 0);
            }
        }
    }
    return memo[a.length() - 1][b.length() - 1];
}

bool test_no_subseq() {
    return 0 == lcs_rec("ABCDEFGH", 0, "IJKLMNOP", 0) &&
           0 == lcs_dyn("ABCDEFGH", "IJKLMNOP");
}

bool test_all_subseq() {
    return 8 == lcs_rec("ABCDEFGH", 0, "ABCDEFGH", 0) &&
           8 == lcs_dyn("ABCDEFGH", "ABCDEFGH");
}

bool test_subseq() {
    return 2 == lcs_rec("ABCD", 0, "EADF", 0) &&
           4 == lcs_rec("AGGTAB", 0, "GXTXAYB", 0) &&
           2 == lcs_dyn("ABCD", "EADF") &&
           4 == lcs_dyn("AGGTAB", "GXTXAYB");
}

int main() {
    int counter = 0;
    if (!test_no_subseq()) {
        counter++;
        cout << "No common subsequence test failed!" << endl;
    }
    if (!test_all_subseq()) {
        counter++;
        cout << "All subsequence test failed!" << endl;
    }
    if (!test_subseq()) {
        counter++;
        cout << "Subsequence test failed!" << endl;
    }
    cout << counter << " test failed." << endl;
}

