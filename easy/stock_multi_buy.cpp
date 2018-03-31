#include <iostream>

// Task description: Given an integer array that contains the prices of a stock
// through a single day, write a method to return the maximum profit if you can
// buy and sell stock multiple times per day.
//
// E.g. for input prices: {100, 180, 260, 310, 40, 535, 695}
//      the method should return: 310 - 100 + 695 - 40 = 865
//
//      for input prices: {790, 720, 670, 480, 410, 340, 280}
//      the method should return: 0
//
// Solution: The implementation below starts at index 0 and identifies the next
// local minimum and local maximum. It then calculates the profit from that
// transaction and continues the same process until the end of the array has
// been reached. The runtime complexity of this approach is O(n) and the space
// complexity is O(1).

int profit(int prices[], int size) {
    int i = 0;
    int max = 0;
    while (i < size) {

        // Find next local minimum.
        while (i < size - 1 && prices[i + 1] <= prices[i]) i++;
        int min = prices[i++];

        // Find local maximum.
        while (i < size - 1 && prices[i + 1] >= prices[i]) i++;
        if (i < size) {
            max += prices[i++] - min;
        }
    }
    return max;
}

bool test_small_array() {
    int prices[] = {100};
    return 0 == profit(prices, 1);
}

bool test_profit() {
    int prices[] = {100, 180, 260, 310, 40, 535, 695};
    return 865 == profit(prices, 7);
}

bool test_no_profit() {
    int prices[] = {790, 720, 670, 480, 410, 340, 280};
    return 0 == profit(prices, 7);
}

int main() {
    int counter = 0;
    if (!test_small_array()) {
        counter++;
        std::cout << "Small array test failed!" << std::endl;
    }
    if (!test_profit()) {
        counter++;
        std::cout << "Profit test failed!" << std::endl;
    }
    if (!test_no_profit()) {
        counter++;
        std::cout << "No profit test failed!" << std::endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

