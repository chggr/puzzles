#include <iostream>

// Task description: Given a stream of integers, implement a data structure to
// store these integers and also efficiently provide the rank of a given value.
// The rank of a value is defined as the number of integers in the stream that
// are less than or equal to that value, excluding itself. If the given value
// has not been received in the stream, the program should return -1.
//
// E.g. for stream: 10, 2, 5, 15, 8, 12, 12, 20
//      the rank of 11 is -1, of 8 is 2 and of 12 is 5.
//
// Solution: A relatively easy way to implement this would be to use a sorted
// array as the underlying data structure. The runtime complexity of insertion
// would be O(n), as we would need to shift on average n/2 elements to insert
// the new value in the correct place. Finding the rank would then be done in
// O(logn) by using binary search to locate the element and return the index.
//
// The implementation below is more efficient and is using a binary tree as the
// underlying data structure. This allows runtime complexity of O(logn) for
// both insertion and ranking. Each node in the tree holds both the value and
// also a counter of all elements less than it. When a new element is inserted,
// the counter is incremented as necessary. Finding the rank is as simple as
// locating the element in the tree and summing up the counter of that node and
// any other parent node where we had to go right.

class Node {

    private:
        Node* left;
        Node* right;
        int value;
        int left_size;

    public:
        Node(int number) : value(number),
                           left(NULL),
                           right(NULL),
                           left_size(0) { }
        void insert(int number);
        int rank(int number);
};

void Node::insert(int number) {
    if (number <= value) {
        if (left == NULL) {
            left = new Node(number);
        } else {
            left->insert(number);
        }
        left_size++;
    } else {
        if (right == NULL) {
            right = new Node(number);
        } else {
            right->insert(number);
        }
    }
}

int Node::rank(int number) {
    if (value == number) {
        return left_size;
    }

    if (number < value) {
        return left == NULL ? -1 : left->rank(number);
    } else {
        int rank = right == NULL ? -1 : right->rank(number);
        return rank == -1 ? -1 : rank + left_size + 1;
    }
}

bool test_rank_not_found() {
    Node root(10);
    root.insert(2);
    root.insert(5);
    root.insert(15);
    root.insert(8);
    root.insert(12);
    root.insert(12);
    root.insert(20);

    return -1 == root.rank(1) &&
           -1 == root.rank(3) &&
           -1 == root.rank(6) &&
           -1 == root.rank(9) &&
           -1 == root.rank(11) &&
           -1 == root.rank(14) &&
           -1 == root.rank(17) &&
           -1 == root.rank(23);
}

bool test_rank() {
    Node root(10);
    root.insert(2);
    root.insert(5);
    root.insert(15);
    root.insert(8);
    root.insert(12);
    root.insert(12);
    root.insert(20);

    return 0 == root.rank(2) &&
           1 == root.rank(5) &&
           2 == root.rank(8) &&
           3 == root.rank(10) &&
           5 == root.rank(12) &&
           6 == root.rank(15) &&
           7 == root.rank(20);
}

int main() {
    int counter = 0;
    if (!test_rank_not_found()) {
        std::cout << "Rank not found test failed!" << std::endl;
        counter++;
    }
    if (!test_rank()) {
        std::cout << "Rank test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

