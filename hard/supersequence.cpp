#include <iostream>
#include <utility>

// Task description: Given two integer arrays, one shorter with all distinct
// elements and one longer, find the shorter sub-sequence in the longer array
// that contains all elements of the shorter array. The items can appear in
// any order.
//
// E.g. for array: {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7}
//      and search sequence: {1, 5, 9}
//      the method should return [7, 10]
//
// Solution: The first implementation below uses a brute force approach to solve
// the task. It goes through all positions in the longer array and for each
// position it scans forward to find the next occurrence of each element of the
// shorter array. The maximum of these occurrences will be the end of the
// shorter sub-sequence that starts at that index and contains all elements in
// the short array. This can be called closure and by finding all of them we
// can identify the shortest sub-sequence overall. The runtime complexity of
// this algorithm is O(S * L^2) where S is the length of the shorter array and
// L is the length of the longer array. This is because for every position in
// the longer array we perform S * L work to search for each element in the
// shorter array through the longer array.
//
// The second implementation is more optimal. It iterates backwards through the
// longer array, keeping track of the last occurrence of each element we are
// searching for. At each position, it uses this information to identify the
// maximum and minimum index of the sub-sequence that contains all elements of
// the shorter array. Its length is calculated and compared to the overall
// minimum. The runtime complexity of this approach is O(L * S) and the space
// complexity is O(S).
//
// The best approach would be to create a map of queues for each element in the
// short array. Then go through the long array and populate the queues so that
// they contain the indices where each element of the short array is found. This
// would take O(L), because both map lookup and queue insertion are O(1)
// operations. Then take the heads of all queues, identify the maximum and put
// them in a min-heap. Iterate while there are elements in the queues and in
// every loop: (1) extract the min index from the min-heap, (2) update the
// sub-sequence indices if max - min is shorter than what has been identified
// up to now, (3) pick up a new element from the queue that provided the min,
// (4) update the max if necessary based on the new element, (5) add the new
// element in the min-heap. This approach would take O(L * log(S)) because
// extracting the min element from a min-heap is a log(n) operation.

using namespace std;

// Returns the target's position in the array after the given index.
int find(int array[], int size, int idx, int target) {
    for (int i = idx; i < size; i++) {
        if (array[i] == target) return i;
    }
    return -1;
}

// Returns the position in array a after the given index which terminates
// a complete sub-array containing all elements of array b.
int find_closure(int a[], int a_size, int b[], int b_size, int idx) {
    int max_idx = -1;
    for (int i = 0; i < b_size; i++) {
        int curr_idx = find(a, a_size, idx, b[i]);
        if (curr_idx == -1) return -1;
        if (curr_idx > max_idx) max_idx = curr_idx;
    }
    return max_idx;
}

pair<int, int> search_brute(int a[], int a_size, int b[], int b_size) {
    pair<int, int> min_pair(0, 0);
    int min_dist = a_size;

    for (int i = 0; i < a_size; i++) {
        int closure = find_closure(a, a_size, b, b_size, i);
        if (closure == -1) continue;
        if (closure - i < min_dist) {
            min_dist = closure - i;
            min_pair.first = i;
            min_pair.second = closure;
        }
    }
    return min_pair;
}

pair<int, int> search_opt(int a[], int a_size, int b[], int b_size) {
    pair<int, int> min_pair(0, 0);
    int min_dist = a_size;
    if (a_size == 0 || b_size == 0) return min_pair;

    int last[b_size] = { -1 };
    for (int i = 0; i < a_size; i++) {
        for (int j = 0; j < b_size; j++) {
            if (a[i] == b[j]) last[j] = i;
        }

        int max = last[0];
        int min = last[0];
        for (int j = 0; j < b_size; j++) {
            if (last[j] > max) max = last[j];
            if (last[j] < min) min = last[j];
        }

        if (min == -1) continue;
        if (max - min < min_dist) {
            min_dist = max - min;
            min_pair.first = min;
            min_pair.second = max;
        }
    }
    return min_pair;
}

bool test_empty() {
    int array[] = {3, 6, 1};

    pair<int, int> bruteA = search_brute(NULL, 0, array, 3);
    pair<int, int> bruteB = search_brute(array, 3, NULL, 0);

    pair<int, int> optA = search_opt(NULL, 0, array, 3);
    pair<int, int> optB = search_opt(array, 3, NULL, 0);

    return 0 == bruteA.first && 0 == bruteA.second &&
           0 == bruteB.first && 0 == bruteB.second &&
           0 == optA.first && 0 == optA.second &&
           0 == optB.first && 0 == optB.second;
}

bool test_larger() {
    int a[] = {7, 0};
    int b[] = {1, 5, 4};

    pair <int, int> brute = search_brute(a, 2, b, 3);
    pair <int, int> opt = search_opt(a, 2, b, 3);

    return 0 == brute.first && 0 == brute.second &&
           0 == opt.first && 0 == opt.second;
}

bool test_not_found() {
    int a[] = {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7};
    int b[] = {1, 5, 4};

    pair<int, int> brute = search_brute(a, 17, b, 3);
    pair<int, int> opt = search_opt(a, 17, b, 3);

    return 0 == brute.first && 0 == brute.second;
           0 == opt.first && 0 == opt.second;
}

bool test_found() {
    int a[] = {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7};
    int b[] = {1, 5, 9};

    pair<int, int> brute = search_brute(a, 17, b, 3);
    pair<int, int> opt = search_opt(a, 17, b, 3);

    return 7 == brute.first && 10 == brute.second &&
           7 == opt.first && 10 == opt.second;
}

int main() {
    int counter = 0;
    if (!test_empty()) {
        cout << "Empty arrays test failed!" << endl;
        counter++;
    }
    if (!test_larger()) {
        cout << "Larger array test failed!" << endl;
        counter++;
    }
    if (!test_not_found()) {
        cout << "Not found test failed!" << endl;
        counter++;
    }
    if (!test_found()) {
        cout << "Found test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

