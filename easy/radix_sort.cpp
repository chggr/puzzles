#include <math.h>
#include <iostream>
#include <queue>
#include <vector>

// Task description: Given an array of positive integers, implement the radix
// sort algorithm to sort the contents of the array in ascending order.
//
// E.g. Input array {8, 2, 11, 5} should be sorted as {2, 5, 8, 11}.
//
// Solution: The implementation below uses the Least Significant Digit (LSD)
// radix sort algorithm to sort the input array. This is a fast and stable
// sorting algorithm that uses buckets to sort the elements of the input array,
// starting from the LSD and moving on to the MSD. The runtime complexity of
// this algorithm is O(m * n) where m is the average key length and n is the
// number of keys. The space complexity is O(n). Queues are used as buckets
// instead of any other data structure so that the relative order is preserved
// and the algorithm remains stable.

using namespace std;

// Uses the nth least significant digit to split input array into buckets.
void bucket(int input[], int size, vector< queue<int> > &buckets, int n) {
    int element;
    int index;

    for (int i = 0; i < size; i++) {
        element = input[i];
        index = (int) (element / pow(10, n)) % 10;
        buckets.at(index).push(element);
    }
}

// Transfers elements from the buckets back into the input array.
void unbucket(int input[], vector< queue<int> > &buckets) {
    int counter = 0;

    for (int i = 0; i < buckets.size(); i++) {
        queue<int> &bucket = buckets.at(i);
        while (!bucket.empty()) {
           input[counter++] = bucket.front();
           bucket.pop();
        }
    }
}

// Counts how many buckets are empty.
int count_empty(vector< queue<int> > &buckets) {
    int empty = 0;
    for (int i = 0; i < buckets.size(); i++) {
        if (buckets.at(i).empty()) empty++;
    }
    return empty;
}

// Sorts the input array using the radix sort algorithm.
void sort(int input[], int size) {
    vector< queue<int> > buckets;
    for (int i = 0; i < 10; i++) {
        buckets.push_back(queue<int>());
    }

    int digit = 0;
    int empty = 0;
    while (empty < 9) {
        bucket(input, size, buckets, digit++);
        empty = count_empty(buckets);
        unbucket(input, buckets);
    }
}

bool test_bucket() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector< queue<int> > buckets;
    for (int i = 0; i < 10; i++) {
       buckets.push_back(queue<int>());
    }

    bucket(input, 10, buckets, 0);
    for (int i = 0; i < 10; i++) {
        queue<int> bucket = buckets.at(i);
        if (bucket.size() != 1) return false;
        if (bucket.front() != i) return false;
    }
    return true;
}

bool test_unbucket() {
    int input[10] = {0};
    vector< queue<int> > buckets;
    for (int i = 0; i < 10; i++) {
        queue<int> bucket;
        bucket.push(i);
        buckets.push_back(bucket);
    }

    unbucket(input, buckets);
    for (int i = 0; i < 10; i++) {
        if (input[i] != i) return false;
    }
    return true;
}

bool is_sorted(int input[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (input[i] > input[i + 1]) return false;
    }
    return true;
}

bool test_sort() {
    int input[] = {34, 54, 73, 15, 8, 112, 1};
    sort(input, 7);
    return is_sorted(input, 7);
}

int main() {
    int counter = 0;
    if (!test_bucket()) {
        cout << "Bucketing test failed!" << endl;
        counter ++;
    }
    if (!test_unbucket()) {
        cout << "Unbucketing test failed!" << endl;
        counter ++;
    }
    if (!test_sort()) {
        cout << "Sort test failed!" << endl;
        counter ++;
    }
    cout << counter << " tests failed." << endl;
}

