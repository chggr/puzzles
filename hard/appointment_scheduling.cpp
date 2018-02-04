#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Task description: Given a sequence of back-to-back appointment requests and
// the requirement to take a 15 minute break between each appointment and the
// next, identify the optimal booking to maximize the total booked minutes.
// Appointment requests are all multiples of 15 minutes, none of them overlap
// and none can be moved. The requirement to take a break between appointments
// means that two adjacent requests cannot both be accepted at the same time.
//
// E.g. for requests {30, 15, 60, 75, 45, 15, 15, 45}
//      the optimal booking is {30, 60, 45, 45}
//
// Solution: A greedy algorithm that first selects the longest appointment, then
// the second longest and so on will not work in this case because the longest
// appointment might not necessarily be part of the optimal solution. E.g. for
// these requests: {15, 45, 90, 60, 15, 15, 30} the optimal booking does not
// contain the longest request: {45, 60, 30}.
//
// The first implementation below is a brute force approach where all possible
// appointment combinations are evaluated. Some combinations are filtered out
// because they are not valid (i.e. back-to-back appointments) and the remaining
// combinations are examined to identify the one with the maximum number of
// booked minutes. The runtime complexity for this approach is O(n * 2^n), where
// n is the number of requested appointments, because for each appointment the
// algorithm evaluates two states: either included or not included in the final
// solution.
//
// The second implementation uses a recursive approach to evaluate at each step
// whether the current appointment should be used or not. If it is used, then
// the next appointment must be skipped. The runtime complexity of this solution
// is O(2^n) because at each step we have to evaluate two choices and this is
// done in total n times, where n is the number of appointments. The space
// complexity is O(n) due to the recursive call stack that grows up to n levels
// deep. Performance can be improved by using memoization to save the result of
// each recursive call for later use. This will improve runtime complexity to
// O(n) because we only need to evaluate each step one time and there is a total
// of n steps. Space complexity will remain O(n).
//
// The third implementation is iterative with runtime complexity of O(n), but
// better space requirements than the recursive solution because no further
// stack space is used. It is based on the observation that three consecutive
// appointments should never be skipped because in that case we could book the
// middle appointment and obtain an improved solution. This means that if we
// take one element at position i, we must definitely skip the element at
// position i + 1 but we must take the element either in position i + 2 or in
// position i + 3. The algorithm below goes through the array from back to
// front, evaluating one position at a time and deciding whether it should be
// included in the final result or not.

using namespace std;

// Returns true only if this is a valid booking
bool isValid(int num, int size) {
    for (int i = 0; i < size; i++) {
        int curr = num & (1 << i);
        int prev = num & (1 << (i + 1));

        // Back-to-back bookings are not allowed.
        if (curr != 0 && prev != 0) return false;
    }
    return true;
}

vector<int> book_brute(int requests[], int size) {
    int max_hours = 0;
    int max_booking = 0;
    for (int i = 1; i < pow(2, size); i++) {
        if (!isValid(i, size)) continue;

        int hours = 0;
        for (int j = 0; j < size; j++) {
            if (i & (1 << j)) hours += requests[j];
        }
        if (hours > max_hours) {
            max_hours = hours;
            max_booking = i;
        }
    }

    vector<int> result;
    for (int i = 0; i < size; i++) {
        if ((max_booking & (1 << i)) != 0) {
            result.push_back(requests[i]);
        }
    }
    return result;
}

void push_back(vector<int>& source, vector<int>& target) {
    for (int i = 0; i < source.size(); i++) {
        target.push_back(source.at(i));
    }
}

int max_minutes(int requests[], int size, int idx, vector<int>& res) {
    if (idx >= size) return 0;

    vector<int> take_vec;
    int take = requests[idx] + max_minutes(requests, size, idx + 2, take_vec);
    take_vec.push_back(requests[idx]);

    vector<int> ignore_vec;
    int ignore = max_minutes(requests, size, idx + 1, ignore_vec);

    if (take >= ignore) {
        push_back(take_vec, res);
        return take;
    }
    push_back(ignore_vec, res);
    return ignore;
}

vector<int> book_rec(int requests[], int size) {
    vector<int> results;
    max_minutes(requests, size, 0, results);
    reverse(results.begin(), results.end());
    return results;
}

vector<int> book_iter(int requests[], int size) {
    int one_away = 0;
    vector<int> one_away_vec;

    int two_away = 0;
    vector<int> two_away_vec;

    int current = 0;
    vector<int> current_vec;

    int take = 0;
    int ignore = 0;
    for (int i = size - 1; i >= 0; i--) {
        take = requests[i] + two_away;
        ignore = one_away;

        if (take >= ignore) {
            current = take;
            current_vec = two_away_vec;
            current_vec.push_back(requests[i]);
        } else {
            current = ignore;
            current_vec = one_away_vec;
        }

        two_away = one_away;
        two_away_vec = one_away_vec;
        one_away = current;
        one_away_vec = current_vec;
    }
    reverse(one_away_vec.begin(), one_away_vec.end());
    return one_away_vec;
}

// Checks whether a vector is equal to an array.
bool equal(vector<int> a, int b[], int size) {
    if (a.size() != size) return false;
    for (int i = 0; i < size; i++) {
        if (a.at(i) != b[i]) return false;
    }
    return true;
}

bool test_no_appointment() {
    vector<int> brute = book_brute(NULL, 0);
    vector<int> recurse = book_rec(NULL, 0);
    vector<int> iter = book_iter(NULL, 0);
    return brute.empty() && recurse.empty() && iter.empty();
}

bool test_one_appointment() {
    int in[] = {30};
    int out[] = {30};

    vector<int> brute = book_brute(in, 1);
    vector<int> recurse = book_rec(in, 1);
    vector<int> iter = book_iter(in, 1);

    return equal(brute, out, 1) &&
           equal(recurse, out, 1) &&
           equal(iter, out, 1);
}

bool test_two_appointments() {
    int inA[] = {30, 45};
    int outA[] = {45};

    int inB[] = {45, 30};
    int outB[] = {45};

    vector<int> bruteA = book_brute(inA, 2);
    vector<int> bruteB = book_brute(inB, 2);

    vector<int> recurseA = book_rec(inA, 2);
    vector<int> recurseB = book_rec(inB, 2);

    vector<int> iterA = book_iter(inA, 2);
    vector<int> iterB = book_iter(inB, 2);

    return equal(bruteA, outA, 1) && equal(bruteB, outB, 1) &&
           equal(recurseA, outA, 1) && equal(recurseB, outB, 1) &&
           equal(iterA, outA, 1) && equal(iterB, outB, 1);
}

bool test_three_appointments() {
    int inA[] = {30, 60, 15};
    int outA[] = {60};

    int inB[] = {60, 30, 15};
    int outB[] = {60, 15};

    vector<int> bruteA = book_brute(inA, 3);
    vector<int> bruteB = book_brute(inB, 3);

    vector<int> recurseA = book_rec(inA, 3);
    vector<int> recurseB = book_rec(inB, 3);

    vector<int> iterA = book_iter(inA, 3);
    vector<int> iterB = book_iter(inB, 3);

    return equal(bruteA, outA, 1) && equal(bruteB, outB, 2) &&
           equal(recurseA, outA, 1) && equal(recurseB, outB, 2) &&
           equal(iterA, outA, 1) && equal(iterB, outB, 2);
}

bool test_many_appointments() {
    int inA[] = {30, 15, 60, 75, 45, 15, 15, 45};
    int outA[] = {30, 60, 45, 45};

    int inB[] = {15, 45, 60, 75, 45, 15, 15, 45};
    int outB[] = {45, 75, 15, 45};

    int inC[] = {75, 105, 120, 75, 90, 135};
    int outC[] = {75, 120, 135};

    vector<int> bruteA = book_brute(inA, 8);
    vector<int> bruteB = book_brute(inB, 8);
    vector<int> bruteC = book_brute(inC, 6);

    vector<int> recurseA = book_rec(inA, 8);
    vector<int> recurseB = book_rec(inB, 8);
    vector<int> recurseC = book_rec(inC, 6);

    vector<int> iterA = book_iter(inA, 8);
    vector<int> iterB = book_iter(inB, 8);
    vector<int> iterC = book_iter(inC, 6);

    return equal(bruteA, outA, 4) &&
           equal(bruteB, outB, 4) &&
           equal(bruteC, outC, 3) &&
           equal(recurseA, outA, 4) &&
           equal(recurseB, outB, 4) &&
           equal(recurseC, outC, 3) &&
           equal(iterA, outA, 4) &&
           equal(iterB, outB, 4) &&
           equal(iterC, outC, 3);
}

int main() {
    int counter = 0;
    if (!test_no_appointment()) {
        cout << "No appointment test failed!" << endl;
        counter++;
    }
    if (!test_one_appointment()) {
        cout << "One appointment test failed!" << endl;
        counter++;
    }
    if (!test_two_appointments()) {
        cout << "Two appointments test failed!" << endl;
        counter++;
    }
    if (!test_three_appointments()) {
        cout << "Three appointments test failed!" << endl;
        counter++;
    }
    if (!test_many_appointments()) {
        cout << "Many appointments test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

