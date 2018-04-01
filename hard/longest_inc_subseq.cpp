#include <iostream>
#include <vector>

// Task description: Given an array of integers, write a method to find the
// length of the longest subsequence such that all elements are sorted in
// ascending order.
//
// E.g. for input array {10, 22, 9, 33, 21, 50, 41, 60, 80}
//      the method should return 6
//
//      for input array {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
//      the method should return 1
//
// Solution: The first implementation below is a brute force approach where we
// iterate through all positions in the input array, calculating the length of
// the longest subsequence starting at that position. We keep track and return
// the maximum length found. The runtime complexity of this approach is O(N^2)
// where N is the length of the array and the space complexity is O(1).
//
// The second implementation is a dynamic programming approach where we create
// a memoization table and fill it in by going through all previous memoized
// results and picking up the longest subsequence that the current element can
// be appended to. The runtime complexity of this algorithm is again O(N^2) and
// the space complexity is O(N).
//
// Finally the third implementation uses a vector to hold at each position the
// smallest integer that ends an increasing sequence of length equal to that
// position. The algorithm iterates through all integers in the input array and
// updates the vector according to the logic below:
//
// - If the integer is greater than the last element in the vector, append it
//   to the end of the vector. This means we have found a new largest LIS.
//
// - Otherwise find the smallest element in the vector which is greater or
//   equal to that integer and change it. The contents of the vector are sorted
//   and therefore we can use binary search to find the place to update in just
//   O(logN).
//
// The total runtime of this algorithm is N * log(N) where N is the total number
// of integers in the input array.

using namespace std;

int lis_brute(int array[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        int value = array[i];
        int length = 1;
        for (int j = i + 1; j < size; j++) {
            if (array[j] > value) {
                length++;
                value = array[j];
            }
        }
        if (length > max) max = length;
    }
    return max;
}

int lis_dyn(int array[], int size) {
    int memo[size] = {0};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (array[j] < array[i] && memo[i] < memo[j] + 1) {
                memo[i] = memo[j] + 1;
            }
        }
        if (memo[i] == 0) memo[i] = 1;
    }

    int max = 0;
    for (int i = 0; i < size; i++) {
        if (memo[i] > max) max = memo[i];
    }
    return max;
}

int binary_search(vector<int> v, int start, int end, int val) {
    if (start > end) return start;

    int mid = (start + end) / 2;
    if (v.at(mid) == val) {
        return mid;
    } else if (v.at(mid) < val) {
        return binary_search(v, mid + 1, end, val);
    } else {
        return binary_search(v, start, mid - 1, val);
    }
}

int lis_opt(int array[], int size) {
    vector<int> memo;
    memo.push_back(array[0]);

    for (int i = 1; i < size; i++) {

        // Element is bigger than last, append.
        if (array[i] > memo.back()) {
            memo.push_back(array[i]);
            continue;
        }

        // Element is smaller than last, search and replace.
        int pos = binary_search(memo, 0, memo.size() - 1, array[i]);
        memo.at(pos) = array[i];
    }
    return memo.size();
}

bool test_binary_search() {
    int values[] = {1, 3, 5, 6, 8, 9};
    vector<int> v(values, values + 6);

    return 1 == binary_search(v, 0, 5, 3) &&
           5 == binary_search(v, 0, 5, 9) &&
           6 == binary_search(v, 0, 5, 12) &&
           1 == binary_search(v, 0, 5, 2);
}

bool test_elements_same() {
    int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    return 1 == lis_brute(array, 10) &&
           1 == lis_dyn(array, 10) &&
           1 == lis_opt(array, 10);
}

bool test_no_lis() {
    int array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    return 1 == lis_brute(array, 10) &&
           1 == lis_dyn(array, 10) &&
           1 == lis_opt(array, 10);
}

bool test_lis() {
    int array[] = {10, 22, 9, 33, 21, 50, 41, 60, 80, 11};
    return 6 == lis_brute(array, 10) &&
           6 == lis_dyn(array, 10) &&
           6 == lis_dyn(array, 10);
}

int main() {
    int counter = 0;
    if (!test_binary_search()) {
        counter++;
        cout << "Binary serach test failed!" << endl;
    }
    if (!test_elements_same()) {
        counter++;
        cout << "Array with same elements test failed!" << endl;
    }
    if (!test_no_lis()) {
        counter++;
        cout << "No LIS test failed!" << endl;
    }
    if (!test_lis()) {
        counter++;
        cout << "LIS test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

