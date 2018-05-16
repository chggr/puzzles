#include <algorithm>
#include <iostream>
#include <queue>

// Task description: Given an array of decimal digits, find the largest multiple
// of three that can be formed using the elements in the array.
//
// E.g. for input array {1, 0} the method should return 0
//      for input array {4, 5} the method should return 54
//
// Solution: The brute force approach would be to generate all possible
// combinations of the given digits and check whether each combination is
// divisible by 3. The runtime complexity of this approach would be O(N! * 2^N).
// This is because there are 2^N possible subsets and for each subset we need to
// calculate all possible permutations.
//
// The implementation below is solving the problem much more efficiently by
// taking into account the following facts for numbers divisible by 3:
// (1) The sum of all digits is also divisible by 3.
// (2) Rearranging the digits also produces a number divisible by 3.
//
// We first sort the input array of digits and then calculate their sum. If this
// is divisible by 3, then we just need to return the integer formed by all
// digits in decreasing order. If it is not divisible by 3, we need to exclude
// one or more digits from the solution. To do this, we create three queues and
// we split the digits based on the remainder of their division by 3. We then
// exclude the smallest digits as required and return the final integer. Both
// the runtime and space complexity of this approach is O(N).

using namespace std;

int toInt(int array[], int size) {
    int result = 0;
    for (int i = size - 1; i >= 0; i--) {
        result *= 10;
        result += array[i];
    }
    return result;
}

int largestMultiple(int array[], int size) {
    sort(array, array + size);

    // Calculate sum of digits.
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    // If the sum of digits is divisible by 3, then the number formed by
    // the array will also be divisible by three.
    if (sum % 3 == 0) return toInt(array, size);

    // Split digits into three queues according to the remainder.
    queue<int> zero;
    queue<int> one;
    queue<int> two;
    for (int i = 0; i < size; i++) {
        int modulo = array[i] % 3;
        if (modulo == 0) {
            zero.push(array[i]);
        } else if (modulo == 1) {
            one.push(array[i]);
        } else {
            two.push(array[i]);
        }
    }

    // If the sum of digits has remainder equal to one, pop one element from
    // queue one or two elements from queue two.
    if (sum % 3 == 1) {
        if (!one.empty()) {
            one.pop();
        } else if (two.size() >= 2) {
            two.pop();
            two.pop();
        } else {
            return 0;
        }
    }

    // If the sum of digits has remainder equal to two, pop one element from
    // queue two or two elements from queue one.
    if (sum % 3 == 2) {
        if (!two.empty()) {
            two.pop();
        } else if (one.size() >= 2) {
            one.pop();
            one.pop();
        } else {
            return 0;
        }
    }

    // Merge queues and return the result.
    int mergeSize = zero.size() + one.size() + two.size();
    int merged[mergeSize];
    int index = 0;
    while (!zero.empty()) {
        merged[index++] = zero.front();
        zero.pop();
    }
    while (!one.empty()) {
        merged[index++] = one.front();
        one.pop();
    }
    while (!two.empty()) {
        merged[index++] = two.front();
        two.pop();
    }
    sort(merged, merged + mergeSize);
    return toInt(merged, mergeSize);
}

bool testToInt() {
    int input[] = {1, 2, 3, 4, 5};
    return 54321 == toInt(input, 5);
}

bool testOneDigit() {
    int inputA[] = {0};
    int inputB[] = {1};
    int inputC[] = {2};
    int inputD[] = {3};

    return 0 == largestMultiple(inputA, 1) &&
           0 == largestMultiple(inputB, 1) &&
           0 == largestMultiple(inputC, 1) &&
           3 == largestMultiple(inputD, 1);
}

bool testTwoDigits() {
    int inputA[] = {0, 1};
    int inputB[] = {2, 3};
    int inputC[] = {4, 5};
    int inputD[] = {3, 9};

    return 0 == largestMultiple(inputA, 2) &&
           3 == largestMultiple(inputB, 2) &&
           54 == largestMultiple(inputC, 2) &&
           93 == largestMultiple(inputD, 2);
}

bool testManyDigits() {
    int inputA[] = {8, 1, 9};
    int inputB[] = {0, 1, 8, 6, 7};

    return 981 == largestMultiple(inputA, 3) &&
           8760 == largestMultiple(inputB, 5);
}

int main() {
    int counter = 0;
    if (!testToInt()) {
        counter++;
        cout << "ToInt test failed!" << endl;
    }
    if (!testOneDigit()) {
        counter++;
        cout << "One digit test failed!" << endl;
    }
    if (!testTwoDigits()) {
        counter++;
        cout << "Two digits test failed!" << endl;
    }
    if (!testManyDigits()) {
        counter++;
        cout << "Many digits test failed!" << endl;
    }
    cout << counter << " tests failed." << endl;
}

