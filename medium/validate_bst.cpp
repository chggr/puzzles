#include <iostream>

// Task description: Given the root of a binary tree, implement an algorithm to
// check whether this is a valid Binary Search Tree (BST).
//
// E.g. The first tree below is a valid BST, whereas the second tree is not.
//
//                    3                      3
//                 2     5                2     5
//              1      4   6           1      2   6
//
// Solution: For this task it is not enough to simply check for each node that
// its value is greater than the value of its left child and less than or equal
// to the value of its right child. The second tree above satisfies this
// description but it is clearly not a binary search tree.
//
// There are two ways to solve this problem. One approach is to extract the
// data in the binary tree sequentially and insert it into an array. Then check
// if the array is sorted. This solution does not work when there are duplicate
// values in the tree, as it cannot differentiate the order with which they
// appear in the tree. The runtime complexity of this solution is O(N) and its
// space complexity is also O(N) as it needs additional array.
//
// The second approach is to recursively check that each node in the binary tree
// is valid by passing the maximum and minimum valid values in the recursive
// function. The implementation below follows this approach and uses -1 as a
// special value to indicate no min or max applies. The runtime complexity of
// this solution is O(N) and space complexity is O(logN), due to the stack
// space required to run the function recursively.

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

bool is_bst(Node* node, int min, int max) {
    if (!node) return true;

    Node* left = node->getLeft();
    Node* right = node->getRight();
    int value = node->getValue();

    if ((min > -1 && value <= min) ||
        (max > -1 && value > max))  return false;

    return is_bst(left, min, node->getValue()) &&
           is_bst(right, node->getValue(), max);
}

bool test_bst_one_node() {
    Node root(1, 0, 0);

    return is_bst(&root, -1, -1);
}

bool test_bst() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node rightleft(4, 0, 0);
    Node rightright(6, 0, 0);
    Node right(5, &rightleft, &rightright);
    Node root(3, &left, &right);

    return is_bst(&root, -1, -1);
}

bool test_not_bst() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node rightleft(2, 0, 0);
    Node rightright(6, 0, 0);
    Node right(5, &rightleft, &rightright);
    Node root(3, &left, &right);

    return !is_bst(&root, -1, -1);
}

int main() {
    int counter = 0;
    if (!test_bst_one_node()) {
        std::cout << "One node BST test failed!" << std::endl;
        counter++;
    }
    if (!test_bst()) {
        std::cout << "BST test failed!" << std::endl;
        counter++;
    }
    if (!test_not_bst()) {
        std::cout << "Not BST test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

