#include <iostream>

#define INT_BITS 32

// Task description: Create a BitSet class that will be used to hold a given
// number of bits in memory. The class should provide functionality to get, set
// and unset each bit individually.

using namespace std;

class BitSet {

    private:
        unsigned size;
        int *bits;

    public:
        BitSet(unsigned size);
        ~BitSet();
        bool get(unsigned pos);
        void set(unsigned pos);
        void unset(unsigned pos);
};

BitSet::BitSet(unsigned size) : size(size) {
    bits = new int[size / INT_BITS + 1] { 0 };
}

BitSet::~BitSet() {
    delete(bits);
}

bool BitSet::get(unsigned pos) {
    if (pos >= size) {
        throw out_of_range("Position is out of range");
    }

    int index = pos / INT_BITS;
    int bit = pos % INT_BITS;
    return (bits[index] & (1 << bit)) > 0;
}

void BitSet::set(unsigned pos) {
    if (pos >= size) {
        throw out_of_range("Position is out of range");
    }

    int index = pos / INT_BITS;
    int bit = pos % INT_BITS;
    bits[index] = bits[index] | (1 << bit);
}

void BitSet::unset(unsigned pos) {
    if (pos >= size) {
        throw out_of_range("Position is out of range");
    }

    int index = pos / INT_BITS;
    int bit = pos % INT_BITS;
    bits[index] = bits[index] & ~(1 << bit);
}

bool test_constructor() {
    BitSet bits(100);
    for (int i = 0; i < 100; i++) {
        if (bits.get(i)) {
           return false;
        }
    }
    return true;
}

bool test_get_out_of_range() {
    BitSet bits(100);
    try {
        bits.get(101);
        return false;
    } catch (const out_of_range& e) {
        return true;
    }
}

bool test_set_out_of_range() {
    BitSet bits(100);
    try {
        bits.set(101);
        return false;
    } catch (const out_of_range& e) {
        return true;
    }
}

bool test_unset_out_of_range() {
    BitSet bits(100);
    try {
        bits.unset(101);
        return false;
    } catch (const out_of_range& e) {
        return true;
    }
}

bool test_get_set_unset() {
    BitSet bits = BitSet(100);
    bits.set(10);
    bits.set(20);
    bits.unset(10);
    return !bits.get(10) && bits.get(20) && !bits.get(30);
}

int main() {
    int counter = 0;
    if (!test_constructor()) {
        cout << "BitSet constructor test failed." << endl;
        counter++;
    }
    if (!test_get_out_of_range()) {
        cout << "BitSet get out of range test failed." << endl;
        counter++;
    }
    if (!test_set_out_of_range()) {
        cout << "BitSet set out of range test failed." << endl;
        counter++;
    }
    if (!test_unset_out_of_range()) {
        cout << "BitSet unset out of range test failed." << endl;
        counter++;
    }
    if (!test_get_set_unset()) {
        cout << "BitSet test failed." << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

