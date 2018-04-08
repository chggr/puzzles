#include <iostream>
#include <string>

// Task description: Given two strings, write a method to return the length of
// the shortest common supersequence.
//
// E.g. for strings "AGGTAB" and "GXTXAYB"
//      the method should return 9 ("AGXGTXAYB")
//
// Solution: This problem is closely related to the problem of finding the
// longest common subsequence in the two strings. Indeed if we know the longest
// common subsequence, the final result would be equal to the sum of the
// strings' lengths minus the length of the longest common subsequence.
//
// Two alternative solutions are presented below. The first implementation is
// recursive: It starts at the beginning of each string and checks whether the
// characters at each position match. If they do, then we need to increment both
// indices. If not, increment either one and return the minimum result. The base
// case is when we have reached the end of one string. In this case we just need
// to return the count of remaining characters of the other string. The runtime
// complexity of this approach is exponential O(2 ^ N) and therefore not
// acceptable.
//
// The second implementation uses dynamic programming to build the final result
// from the ground up. It creates an MxN memoization matrix to store solutions
// to intermediate subproblems. It then fills the matrix from the bottom up
// using similar logic as the previous recursive implementation. The runtime
// complexity of this approach is O(N * M) which is much better than before. The
// space complexity is also O(N * M) for the memoization matrix.

using namespace std;

int scs_rec(string a, int idx_a, string b, int idx_b) {

    // Base cases, we have reached the end of one string.
    if (idx_a >= a.length()) return b.length() - idx_b;
    if (idx_b >= b.length()) return a.length() - idx_a;

    if (a[idx_a] == b[idx_b]) {
        return 1 + scs_rec(a, idx_a + 1, b, idx_b + 1);
    }

    return min(1 + scs_rec(a, idx_a + 1, b, idx_b),
               1 + scs_rec(a, idx_a, b, idx_b + 1));
}

int scs_dyn(string a, string b) {
    int memo[a.length() + 1][b.length() + 1];
    for (int i = 0; i <= a.length(); i++) {
        for (int j = 0; j <= b.length(); j++) {
            if (i == 0) {
                memo[i][j] = j;
            } else if (j == 0) {
                memo[i][j] = i;
            } else if (a[i - 1] == b[j - 1]) {
                memo[i][j] = 1 + memo[i - 1][j - 1];
            } else {
                memo[i][j] = min(1 + memo[i - 1][j], 1 + memo[i][j - 1]);
            }
        }
    }

    return memo[a.length()][b.length()];
}

bool test_max_superseq() {
    return 16 == scs_rec("ABCDEFGH", 0, "IJKLMNOP", 0) &&
           16 == scs_dyn("ABCDEFGH", "IJKLMNOP");
}

bool test_min_superseq() {
    return 8 == scs_rec("ABCDEFGH", 0, "ABCDEFGH", 0) &&
           8 == scs_dyn("ABCDEFGH", "ABCDEFGH");
}

bool test_superseq() {
    return 14 == scs_rec("ABCDEFGH", 0, "IJKLCNHP", 0) &&
           9 == scs_rec("AGGTAB", 0, "GXTXAYB", 0) &&
           14 == scs_dyn("ABCDEFGH", "IJKLCNHP") &&
           9 == scs_dyn("AGGTAB", "GXTXAYB");
}

int main() {
    int counter = 0;
    if (!test_max_superseq()) {
        counter++;
        cout << "Max supersequence test failed!" << endl;
    }
    if (!test_min_superseq()) {
        counter++;
        cout << "Min supersequence test failed!" << endl;
    }
    if (!test_superseq()) {
        counter++;
        cout << "Supersequence test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

