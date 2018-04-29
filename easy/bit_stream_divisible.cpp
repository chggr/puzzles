#include <iostream>

// Task description: Given a stream of bits, write a method to return whether
// the number formed so far is divisible by a given factor. The stream is
// possible infinite and too large to fit in main memory as one number.
//
// E.g. given stream 1110 and factor 7, the answer is true.
//      given stream 1101 and factor 7, the answer is false.
//
// Solution: A naive approach would be to store the input bit stream as a number
// and check divisibility by the given factor. This will cause overflow though
// for large bit streams. The implementation below overcomes this limitation by
// just maintaining the remainder in memory. When the next bit is consumed, the
// remainder is multiplied by 2 (i.e. shifted by one position) and the bit is
// added to the result. The new remainder is then calculated and the process is
// repeated for all bits in the stream. If the current remainder is zero then
// this means that the number formed so far is divisible by the given factor.

class Stream {

    private:
        int factor;
        int remainder;

    public:
        Stream(int factor) : factor(factor), remainder(0) {}

        Stream& next(bool bit) {
            remainder <<= 1;
            if (bit) remainder++;
            remainder %= factor;
            return *this;
        }

        bool divisible() {
            return remainder == 0;
        }
};

bool test_empty() {
    Stream stream(7);
    return stream.divisible();
}

bool test_divisible() {
    Stream stream(7);
    stream.next(1).next(1).next(1).next(0);
    return stream.divisible();
}

bool test_not_divisible() {
    Stream stream(7);
    stream.next(1).next(1).next(0).next(1);
    return !stream.divisible();
}

int main() {
    int counter = 0;
    if (!test_empty()) {
        counter++;
        std::cout << "Empty stream test failed!" << std:: endl;
    }
    if (!test_divisible()) {
        counter++;
        std::cout << "Divisible stream test failed!" << std:: endl;
    }
    if (!test_not_divisible()) {
        counter++;
        std::cout << "Not divisible stream test failed!" << std:: endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

