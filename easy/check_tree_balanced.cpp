#include <iostream>
#include <algorithm>

// Task description: Given the root of a binary tree, write a method to
// determine whether the tree is balanced. A balanced binary tree is a tree
// such that the heights of the two subtrees under any node never differ by
// more than one.

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

int height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(height(node->getLeft()), height(node->getRight()));
}

bool is_balanced(Node* node) {
    if (!node) return true;

    int height_left = height(node->getLeft());
    int height_right = height(node->getRight());
    return abs(height_left - height_right) <= 1 &&
           is_balanced(node->getLeft()) &&
           is_balanced(node->getRight());
}

bool test_tree_one_node() {
    Node root(1, 0, 0);

    return is_balanced(&root);
}

bool test_tree_balanced() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node right(3, 0, 0);
    Node root(4, &left, &right);

    return is_balanced(&root);
}

bool test_tree_not_balanced() {
    Node leftleftleft(1, 0, 0);
    Node leftleft(2, &leftleftleft, 0);
    Node left(3, &leftleft, 0);
    Node root(4, &left, 0);

    return !is_balanced(&root);
}

int main() {
    int counter = 0;
    if (!test_tree_one_node()) {
        std::cout << "One node tree test failed!" << std::endl;
        counter++;
    }
    if (!test_tree_balanced()) {
        std::cout << "Tree balanced test failed!" << std::endl;
        counter++;
    }
    if (!test_tree_not_balanced()) {
        std::cout << "Tree not balanced test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

