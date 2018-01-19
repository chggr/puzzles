#include <iostream>

// Task description: Given an unstable sorting algorithm, what is the best way
// to make it stable without changing how it works?
//
// Solution: A stable sorting algorithm preserves the relative order of elements
// with equal keys whereas an unstable algorithm does not. When the data set
// being sorted has keys that are equal, a stable algorithm will potentially
// yield different result than an unstable algorithm. If the data set does not
// have equal keys though, both stable and unstable algorithms will produce the
// same results. Therefore the best way to make an unstable sorting algorithm
// stable is to ensure there are no equal keys in the data set.
//
// The implementation below uses wrapper class Item to wrap every element in the
// data set being sorted. It holds both the element and its position in the
// original data set. To make an unstable algorithm stable, we just need to
// extend the sorting key to also include the position of each element in the
// original array.
//
// The selection_sort() method implements selection sort which is inherently
// unstable. If we use a comparator function that only takes into account each
// element's value (i.e. unstable_compare()), then the relative order of the
// elements will not be preserved in the result. On the contrary, if we use a
// comparator function that also takes into account the position of each element
// in the original array (i.e. stable_compare()), the algorithm becomes stable.
// The space complexity of this solution is O(n), as it requires one extra
// integer per element. The runtime complexity is equal to the complexity of
// the underlying sorting algorithm, which is O(n^2) for selection sort.

template <class T>
class Item {

    private:
        T value;
        int seq;

    public:
        Item(T value) : value(value), seq(0) { }
        Item(T value, int seq) : value(value), seq(seq) { }
        T getValue() const { return value; }
        void setValue(T v) { value = v; }
        int getSeq() const { return seq; };
        void setSeq(int s) { seq = s; }
};

template <class T>
void selection_sort(Item<T> array[], int size,
                    bool (*compare)(Item<T> a, Item<T> b)) {

    for (int i = 0; i < size; i++) {

        // Find the min in the remainder of the array.
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (compare(array[j], array[min_idx])) {
                min_idx = j;
            }
        }

        // Swap with current element.
        if (min_idx != i) {
            Item<T> temp = array[i];
            array[i] = array[min_idx];
            array[min_idx] = temp;
        }
    }
}

// Only compares values, cannot stabilize an unstable sort.
template <class T>
bool unstable_compare(Item<T> a, Item<T> b) {
    return a.getValue() < b.getValue();
}

// Compares values and sequence ids, can stabilize an unstable sort.
template <class T>
bool stable_compare(Item<T> a, Item<T> b) {
    return a.getValue() == b.getValue() ?
        a.getSeq() < b.getSeq() : a.getValue() < b.getValue();
}

template <class T>
bool are_equal(Item<T> a[], Item<T> b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i].getValue() != b[i].getValue() ||
            a[i].getSeq() != b[i].getSeq()) return false;
    }
    return true;
}

bool test_unstable_compare() {
    return !unstable_compare(Item<int>(1, 0), Item<int>(1, 1)) &&
           !unstable_compare(Item<int>(1, 1), Item<int>(1, 0)) &&
           !unstable_compare(Item<int>(2, 0), Item<int>(1, 1)) &&
           unstable_compare(Item<int>(1, 0), Item<int>(2, 1));
}

bool test_stable_compare() {
    return stable_compare(Item<int>(1, 0), Item<int>(1, 1)) &&
           !stable_compare(Item<int>(1, 1), Item<int>(1, 0)) &&
           !stable_compare(Item<int>(2, 0), Item<int>(1, 1)) &&
           stable_compare(Item<int>(1, 0), Item<int>(2, 1));
}


bool test_unstable_sort() {
    Item<int> input[] = { Item<int>(5, 0), Item<int>(8, 1), Item<int>(3, 2),
        Item<int>(5, 3), Item<int>(1, 4), Item<int>(2, 5), Item<int>(7, 6) };

    Item<int> expected[] = { Item<int>(1, 4), Item<int>(2, 5), Item<int>(3, 2),
        Item<int>(5, 3), Item<int>(5, 0), Item<int>(7, 6), Item<int>(8, 1) };

    selection_sort(input, 7, &unstable_compare);
    return are_equal(input, expected, 7);
}

bool test_stable_sort() {
    Item<int> input[] = { Item<int>(5, 0), Item<int>(8, 1), Item<int>(3, 2),
        Item<int>(5, 3), Item<int>(1, 4), Item<int>(2, 5), Item<int>(7, 6) };

    Item<int> expected[] = { Item<int>(1, 4), Item<int>(2, 5), Item<int>(3, 2),
        Item<int>(5, 0), Item<int>(5, 3), Item<int>(7, 6), Item<int>(8, 1) };

    selection_sort(input, 7, &stable_compare);
    return are_equal(input, expected, 7);
}

int main() {
    int counter = 0;
    if (!test_unstable_compare()) {
        std::cout << "Unstable compare test failed!" << std::endl;
        counter++;
    }
    if (!test_stable_compare()) {
        std::cout << "Stable compare test failed!" << std::endl;
        counter++;
    }
    if (!test_unstable_sort()) {
        std::cout << "Unstable sort test failed!" << std::endl;
        counter++;
    }
    if (!test_stable_sort()) {
        std::cout << "Stable sort test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

