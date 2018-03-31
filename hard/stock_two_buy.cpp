#include <iostream>
#include <climits>

// Task description: Given an integer array that contains the prices of a stock
// through a single day, write a method to return the maximum profit if you can
// buy and sell stock only twice per day.
//
// E.g. for input prices: {4, 6, 9, 3, 2, 5, 8, 4, 6, 9}
//      the method should return: 9 - 4 + 9 - 2 = 12
//
//      for input prices: {9, 8, 7, 6, 5, 4, 3, 2, 1}
//      the method should return: 0
//
// Solution: The implementation below uses a dynamic programming approach to
// calculate the maximum profit of doing just two transactions on the input
// price array. The following list outlines the variables used and how they are
// updated. The runtime complexity of this algorithm is O(n) and the space
// complexity is just O(1).
//
// 1) buyFirst: The lowest price we can buy stock in the first transaction,
//              calculated as the minimum of the previous value and the current
//              price.
//
// 2) sellFirst: The maximum profit we can make by selling stock in the first
//               transaction, calculated as the maximum of the previous value
//               and the current price minus the price the stock was bought.
//
// 3) buySecond: The lowest price we can buy in the second transaction. This is
//               calculated as the minimum of the previous value and the current
//               price after taking into account the profit made in the first
//               transaction. The latter is required so that variable sellSecond
//               contains the maximum profit achieved for both transactions.
//
// 4) sellSecond: The maximum profit achieved for both transactions, calculated
//                as the maximum of the previous value and the current price
//                minus the price the stock was bought.

int max (int a, int b) {
    return a > b ? a : b;
}

int min (int a, int b) {
    return a < b ? a : b;
}

int profit(int prices[], int size) {

    int buyFirst = INT_MAX;
    int sellFirst = 0;
    int buySecond = INT_MAX;;
    int sellSecond = 0;

    for (int i = 0; i < size; i++) {

        // Second stock
        sellSecond = max(sellSecond, prices[i] - buySecond);
        buySecond = min(buySecond, prices[i] - sellFirst);

        // First stock
        sellFirst = max(sellFirst, prices[i] - buyFirst);
        buyFirst = min(buyFirst, prices[i]);
    }

    return sellSecond;
}

bool test_small_array() {
    int prices[] = {100};
    return 0 == profit(prices, 1);
}

bool test_profit() {
    int prices[] = {4, 6, 9, 3, 2, 5, 8, 4, 6, 9};
    return 12 == profit(prices, 10);
}

bool test_no_profit() {
    int prices[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    return 0 == profit(prices, 10);
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

