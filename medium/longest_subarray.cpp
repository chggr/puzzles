#include <iostream>
#include <map>

// Task description: Given an integer array filled with ones and zeros, find the
// longest sub-array that contains the same number of ones and zeros.
//
// E.g. for array: {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1}
//      the longest sub-array starts at index 3 and ends at 12
//
// Solution: The first implementation below uses a brute force algorithm to
// identify the longest sub-array with the same number of ones and zeros. It
// starts with the largest possible sub-array and evaluates all sub-arrays
// until it has found one with the same number of zeros. Returns the start
// and end index of the identified sub-array. The runtime complexity of this
// algorithm is O(N^2).
//
// The second implementation uses an array to store the difference between the
// number of ones and zeros that have been encountered up to and including that
// position. The longest sub-array will be the sub-array where this difference
// is the same before it starts and at the place where it ends. In the example
// below the start of the sub-array is position 3 and the end is position 12.
//
//  original: {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1}
//      diff: {1, 2, 3, 2, 3, 4, 5, 4, 5, 4, 3, 4, 3, 4, 5}
// sub-array:        ^  |--------------------------|

class Range {
    private:
        int start;
        int end;

    public:
        Range(int start, int end) : start(start), end(end) { };
        int getStart() { return start; }
        int getEnd() { return end; }
};

Range longest_subarray_brute(int array[], int size) {
    int ones;
    int zeros;
    for (int len = size; len > 1; len--) {
        for (int i = 0; i <= size - len; i++) {
            ones = 0;
            zeros = 0;
            for (int j = 0; j < len; j++) {
                if (array[i + j]) ones++;
                else zeros++;
            }
            if (ones == zeros) {
                return Range(i, i + len - 1);
            }
        }
    }
    return Range(0, 0);
}

Range longest_subarray(int array[], int size) {

    // Populate diff table with total number of ones minus total number of
    // zeros at each position.
    int diff[size];
    int ones = 0;
    int zeros = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == 1) ones++;
        else zeros++;
        diff[i] = ones - zeros;
    }

    // Use a map to store the index where each diff value first occurred.
    std::map<int,int> first_idx;
    first_idx[0] = -1;

    Range range(0, 0);
    int max = 0;
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (first_idx.find(diff[i]) == first_idx.end()) {
            first_idx[diff[i]] = i;
        } else {
           idx = first_idx[diff[i]];
           if (i - idx > max) {
               range = Range(idx + 1, i);
               max = i - idx;
           }
        }
    }
    return range;
}

bool test_all_ones() {
    int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    Range range = longest_subarray(array, 15);
    return range.getStart() == 0 && range.getEnd() == 0;
}

bool test_brute_all_ones() {
    int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    Range range = longest_subarray_brute(array, 15);
    return range.getStart() == 0 && range.getEnd() == 0;
}

bool test_all_zeros() {
    int array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Range range = longest_subarray(array, 15);
    return range.getStart() == 0 && range.getEnd() == 0;
}

bool test_brute_all_zeros() {
    int array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Range range = longest_subarray_brute(array, 15);
    return range.getStart() == 0 && range.getEnd() == 0;
}

bool test_more_ones() {
    int array[] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1};
    Range range = longest_subarray(array, 15);
    return range.getStart() == 3 && range.getEnd() == 12;
}

bool test_brute_more_ones() {
    int array[] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1};
    Range range = longest_subarray_brute(array, 15);
    return range.getStart() == 3 && range.getEnd() == 12;
}

bool test_more_zeros() {
    int array[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    Range range = longest_subarray(array, 15);
    return range.getStart() == 3 && range.getEnd() == 12;
}

bool test_brute_more_zeros() {
    int array[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    Range range = longest_subarray_brute(array, 15);
    return range.getStart() == 3 && range.getEnd() == 12;
}

bool test_long_subarray() {
    int array[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    Range range = longest_subarray(array, 14);
    return range.getStart() == 0 && range.getEnd() == 13;
}

bool test_brute_long_subarray() {
    int array[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    Range range = longest_subarray_brute(array, 14);
    return range.getStart() == 0 && range.getEnd() == 13;
}

int main() {
    int counter = 0;
    if (!test_all_ones()) {
        std::cout << "All ones test failed!" << std::endl;
        counter++;
    }
    if (!test_brute_all_ones()) {
        std::cout << "All ones brute test failed!" << std::endl;
        counter++;
    }
    if (!test_all_zeros()) {
        std::cout << "All zeros test failed!" << std::endl;
        counter++;
    }
    if (!test_brute_all_zeros()) {
        std::cout << "All zeros brute test failed!" << std::endl;
        counter++;
    }
    if (!test_more_ones()) {
        std::cout << "More ones test failed!" << std::endl;
        counter++;
    }
    if (!test_brute_more_ones()) {
        std::cout << "More ones brute test failed!" << std::endl;
        counter++;
    }
    if (!test_more_zeros()) {
        std::cout << "More zeros test failed!" << std::endl;
        counter++;
    }
    if (!test_brute_more_zeros()) {
        std::cout << "More zeros brute test failed!" << std::endl;
        counter++;
    }
    if (!test_long_subarray()) {
        std::cout << "Long sub-array test failed!" << std::endl;
        counter++;
    }
    if (!test_brute_long_subarray()) {
        std::cout << "Long sub-array brute test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

