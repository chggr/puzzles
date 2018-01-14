#include <algorithm>
#include <iostream>
#include <queue>

// Task description: Design an algorithm to find the kth number such that it
// can be broken down into factors of 3, 5 and 7. What is the runtime complexity
// of your approach, can it be improved?
//
// E.g. The first multiples are: {1, 3, 5, 7, 9, 15, 21}
//
// Solution: This task is basically asking for the kth smallest number that can
// take the form 3^a * 5^b * 7^c.
//
// One simple brute force approach would be to generate all such numbers where
// 0 <= a <= k and 0 <= b <= k and 0 <= c <= k, sort them and pick the kth
// number in the list. This would require three nested loops and a sort. The
// runtime complexity of the nested loops would be O(k^3), producing a total of
// k^3 elements. To sort these elements we would require O(k^3 * log(k^3)),
// which can be simplified to O(k^3 * logk). This is quite slow for large k.
//
// The first implementation below is also brute force but more efficient. It
// goes through all numbers from zero onwards and examines each one of them to
// determine whether it is a multiple or not. The kth multiple is returned as
// soon as it has been found.
//
// The second implementation uses a different approach to further improve
// performance. It is based on the observation that each subsequent number in
// the sequence can be derived by multiplying one of the existing numbers by 3
// or 5 or 7. We create three queues (for 3 / 5 / 7) and every time a new
// multiple is found, we push in each queue the product of that multiple with 3,
// 5 or 7 respectively. To get the next multiple we just need to pick the
// smallest of the heads of the three lists.

// Returns true only if the given number is multiple of 3, 5 and 7.
bool is_multiple(int num) {
    if (num <= 0) return false;

    while(num != 1) {
        if (num % 3 == 0) num /= 3;
        else if (num % 5 == 0) num /= 5;
        else if (num % 7 == 0) num /= 7;
        else return false;
    }
    return true;
}

int get_multiple_brute(int k) {
    if (k <= 0) return 0;

    int counter = 0;
    for (int num = 0;; num++) {
        if (is_multiple(num)) {
            counter++;
            if (counter == k) {
                return num;
            }
        }
    }
}

// Pops and returns the minimum head of the three provided lists.
int get_min(std::queue<int> &three_q,
            std::queue<int> &five_q,
            std::queue<int> &seven_q) {

    int minimum = std::min(three_q.front(), five_q.front());
    minimum = std::min(minimum, seven_q.front());

    if (minimum == three_q.front()) three_q.pop();
    if (minimum == five_q.front()) five_q.pop();
    if (minimum == seven_q.front()) seven_q.pop();
    return minimum;
}

int get_multiple(int k) {
    if (k <= 0) return 0;
    if (k == 1) return 1;

    std::queue<int> three_q;
    std::queue<int> five_q;
    std::queue<int> seven_q;

    three_q.push(3);
    five_q.push(5);
    seven_q.push(7);

    int multiple = 0;
    int minimum = 0;
    for (int i = 2; i <= k; i++) {
        do {
            minimum = get_min(three_q, five_q, seven_q);
        } while (minimum <= multiple);
        multiple = minimum;
        three_q.push(3 * multiple);
        five_q.push(5 * multiple);
        seven_q.push(7 * multiple);
    }
    return multiple;
}

bool test_is_multiple() {
    return !is_multiple(-1) &&
           !is_multiple(0) &&
           is_multiple(1) &&
           !is_multiple(2) &&
           is_multiple(3) &&
           is_multiple(5) &&
           is_multiple(7) &&
           is_multiple(15) &&
           !is_multiple(13);
}

bool test_get_multiple_brute() {
    return 0 == get_multiple_brute(-1) &&
           0 == get_multiple_brute(0) &&
           1 == get_multiple_brute(1) &&
           3 == get_multiple_brute(2) &&
           5 == get_multiple_brute(3) &&
           7 == get_multiple_brute(4) &&
           9 == get_multiple_brute(5) &&
           15 == get_multiple_brute(6) &&
           21 == get_multiple_brute(7);
}

bool test_get_multiple() {
    return 0 == get_multiple(-1) &&
           0 == get_multiple(0) &&
           1 == get_multiple(1) &&
           3 == get_multiple(2) &&
           5 == get_multiple(3) &&
           7 == get_multiple(4) &&
           9 == get_multiple(5) &&
           15 == get_multiple(6) &&
           21 == get_multiple(7);
}

int main() {
    int counter = 0;
    if (!test_is_multiple()) {
        std::cout << "Is multiple test failed!" << std::endl;
        counter++;
    }
    if (!test_get_multiple_brute()) {
        std::cout << "Get multiple brute test failed!" << std::endl;
        counter++;
    }
    if (!test_get_multiple()) {
        std::cout << "Get multiple test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

