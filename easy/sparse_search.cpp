#include <iostream>
#include <string>
#include <vector>

// Task description: Given a sorted vector of strings that also contains many
// empty strings, write a method to find the location of a given string. The
// method should return -1 if the string is part of the vector.
//
// E.g. For input vector: {"a",·"",·"",·"b",·"",·"c",·"",·"",·"",·"d"}
//      string "c" is at location 5.
//
// Solution: The implementation below uses a modified binary search to locate
// the given string inside the input vector. Method find_mid() is used to find
// the middle element that is not an empty string. This element is then used in
// a standard implementation of binary search to search through the input
// vector and return the index of the given string.

using namespace std;

int find_mid(vector<string> &input, int low, int high) {
    int mid = (low + high) / 2;
    if (!input.at(mid).empty()) {
        return mid;
    }

    int right = mid + 1;
    int left = mid - 1;
    while (right <= high || left >= low) {
        if (right <= high && !input.at(right).empty()) {
            return right;
        }
        right++;

        if (left >= low && !input.at(left).empty()) {
            return left;
        }
        left--;
    }
    return -1;
}

int search(vector<string> input, string item) {
    int low = 0;
    int high = input.size() - 1;
    int mid;

    while (low <= high) {
        mid = find_mid(input, low, high);
        if (mid == -1) {
            return -1;
        }
        if (input.at(mid) == item) {
            return mid;
        }
        if (input.at(mid) > item) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

bool test_not_found() {
    vector<string> input = {"a", "", "", "b", "", "c", "", "", "", "d"};
    return -1 == search(input, "e");
}

bool test_not_found_all_empty() {
    vector<string> input = {"", "", "", "", "", "", "", "", "", ""};
    return -1 == search(input, "b");
}

bool test_found() {
    vector<string> input = {"a", "", "", "b", "", "c", "", "", "", "d"};
    return 5 == search(input, "c");
}

bool test_found_last() {
    vector<string> input = {"a", "", "", "b", "", "c", "", "", "", "d"};
    return 0 == search(input, "a");
}

bool test_found_first() {
    vector<string> input = {"a", "", "", "b", "", "c", "", "", "", "d"};
    return 9 == search(input, "d");
}

int main() {
    int counter = 0;
    if (!test_not_found()) {
        cout << "Not found test failed!" << endl;
        counter++;
    }
    if (!test_not_found_all_empty()) {
        cout << "Not found all empty test failed!" << endl;
        counter++;
    }
    if (!test_found()) {
        cout << "Found test failed!" << endl;
        counter++;
    }
    if (!test_found_last()) {
        cout << "Found last element test failed!" << endl;
        counter++;
    }
    if (!test_found_first()) {
        cout << "Found first element test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

