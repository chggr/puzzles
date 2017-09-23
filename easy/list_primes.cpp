#include <iostream>
#include <math.h>
#include <vector>

// Task description: Given an integer n, write a method that returns a list of
// prime numbers that are less than n.
//
// E.g. For n = 30 the answer is: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29} 
//
// Solution: A simple brute force approach would be to go through all numbers
// from 2 up to the given integer and for each one check if it is prime. This
// approach works but is very inefficient.
//
// The implementation below uses a highly efficient algorithm called "The Sieve
// of Eratosthenes" to generate the list of primes. It works by recognizing
// that all non-prime numbers are divisible by a prime number. We iterate from
// 2 up to the root of the given integer and for each value we cross out all
// numbers that are divisible by it. The space complexity of the implementation
// below could be further improved by only storing data for odd numbers, as
// even numbers are de facto non primes. 

using namespace std;

vector<int> get_primes(int max) {
    bool is_prime[max] = { false };
    for (int i = 2; i < max; i++) {
        is_prime[i] = true;
    }

    int root = sqrt(max);
    for (int i = 2; i <= root; i++) {
        if (!is_prime[i]) continue;
        for (int j = 2; i * j < max; j++) {
            is_prime[i * j] = false;
        }
    }

    vector<int> results;
    for (int i = 0; i < max; i++) {
        if (is_prime[i]) {
            results.push_back(i);
        }
    }
    return results;
}

int test_get_primes() {
    vector<int> primes = get_primes(30);

    return 10 == primes.size() && 2 == primes.at(0) &&
           3 == primes.at(1) && 5 == primes.at(2) &&
           7 == primes.at(3) && 11 == primes.at(4) &&
           13 == primes.at(5) && 17 == primes.at(6) &&
           19 == primes.at(7) && 23 == primes.at(8) &&
           29 == primes.at(9);
}

int test_get_primes_large_max() {
    return 1000 == get_primes(7920).size();
}

int main() {
    int counter = 0;
    if (!test_get_primes()) {
        cout << "Get primes test failed!" << endl;
        counter++;
    }
    if (!test_get_primes_large_max()) {
        cout << "Get primes with large max test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

