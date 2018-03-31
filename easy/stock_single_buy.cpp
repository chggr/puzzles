#include <iostream>

// Task description: Given an integer array that contains the prices of a stock
// through a single day, write a method to return the maximum profit if you can
// only buy and sell once.
//
// E.g. for input prices: [2, 3, 10, 6, 4, 8, 1]
//      the method should return: 10 - 2 = 8
//
//      for input prices: [9, 8, 7, 6, 5, 4, 3]
//      the method should return: 0
//
// Solution: The implementation below iterates through the input price array
// once, keeping track of the minimum price seen so far. At each position, it
// calculates the profit and updates the maximum profit overall. The runtime
// complexity of this solution is O(n), where n is the number of prices in the
// input array. The space complexity is O(1).

int profit(int prices[], int size) {
    int maxProfit = 0;
    int minLeft = prices[0];
    for (int i = 1; i < size; i++) {
        if (prices[i] < minLeft) {
            minLeft = prices[i];
            continue;
        }

        if (prices[i] - minLeft > maxProfit) {
            maxProfit = prices[i] - minLeft;
        }
    }
    return maxProfit;
}

bool test_small_array() {
    int prices[] = {1};
    return 0 == profit(prices, 1);
}

bool test_profit() {
    int prices[] = {2, 3, 10, 6, 4, 8, 1};
    return 8 == profit(prices, 7);
}

bool test_no_profit() {
    int prices[] = {9, 8, 7, 6, 5, 4, 3};
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

