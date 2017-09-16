#include <iostream>

// Task description: Given an array of unique integers that is already sorted
// in increasing order, write an algorithm to create a binary search tree with
// minimal height.
//                                                        2
// e.g. For input array {1, 2, 3, 4} it should create   1   3
//                                                            4
//
// Solution: Since the input array is already sorted, the algorithm simply
// needs to be pick up the middle element and set it as the root of the binary
// search tree. This will guarantee that the tree will be balanced and have
// minimal height. Subsequently we can use the standard recursive algorithm to
// insert the remaining elements into the tree. This approach has runtime
// complexity O(N logN).
//
// The implementation below follows a different approach to achieve better
// runtime performance. The extra traversals required to insert each element
// in the tree are not needed, as the recursive algorithm halves the array
// with each recursion and returns the root of the minimal tree for that
// portion of the array.

class Node {

    private:
        Node* left;
        Node* right;
        int value;

    public:
        Node(int value, Node* left, Node* right) :
            value(value), left(left), right(right) { }
        Node* getRight() { return right; }
        Node* getLeft() { return left; }
        int getValue() { return value; }
};

Node* create_tree(int* array, int start, int end) {
    if (end < start) {
        return 0;
    }

    int middle = start + (end - start) / 2;
    Node* left = create_tree(array, start, middle - 1);
    Node* right = create_tree(array, middle + 1, end);
    return new Node(array[middle], left, right);
}

bool is_leaf(Node *node) {
    return 0 == node->getLeft() && 0 == node->getRight();
}

bool test_one_element() {
    int input[] = {1};
    Node* root = create_tree(input, 0, 0);

    return 1 == root->getValue() && is_leaf(root);
}

bool test_odd_elements() {
    int input[] = {1, 2, 3};
    Node* root = create_tree(input, 0, 2);

    return 2 == root->getValue() &&
           1 == root->getLeft()->getValue() &&
           is_leaf(root->getLeft()) &&
           3 == root->getRight()->getValue() &&
           is_leaf(root->getRight());
}

bool test_even_elements() {
    int input[] = {1, 2, 3, 4};
    Node* root = create_tree(input, 0, 3);

    return 2 == root->getValue() &&
           1 == root->getLeft()->getValue() &&
           is_leaf(root->getLeft()) &&
           3 == root->getRight()->getValue() &&
           0 == root->getRight()->getLeft() &&
           4 == root->getRight()->getRight()->getValue() &&
           is_leaf(root->getRight()->getRight());
}

int main() {
    int counter = 0;
    if (!test_one_element()) {
        std::cout << "One element test failed!" << std::endl;
        counter++;
    }
    if (!test_odd_elements()) {
        std::cout << "Odd elements test failed!" << std::endl;
        counter++;
    }
    if (!test_even_elements()) {
        std::cout << "Even elements test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

