#include <iostream>
#include <algorithm>

// Task description: Given the root of a binary tree, write a method to
// determine whether the tree is balanced. A balanced binary tree is a tree
// such that the heights of the two sub-trees under any node never differ by
// more than one.
//
// E.g. the first tree below is balanced whereas the second is not.
//
//          5                     5
//       2     7                2
//     3   4     9            3
//
// Solution: The first solution below recursively checks for every node in the
// tree that its left and right sub-trees have the same height. The runtime
// complexity of this implementation is O(N * logN) because each node is touched
// once per node above it. It is not very efficient, since method height() is
// called repeatedly on the same nodes.
//
// The second implementation combines the operation of getting the height of a
// node with checking whether it is balanced. If the node is not balanced, error
// code -1 is returned which signals that the whole tree is not balanced. This
// code is propagated immediately at the top, thus saving further calls to
// height(). The runtime complexity of this approach is O(N) since each node is
// touched only once. The space complexity is O(D) where D is the depth of the
// tree. This space is required for the recursive stack.

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

int height2(Node* node) {
    if (!node) return 0;

    int height_left = height2(node->getLeft());
    if (height_left == -1) return -1;

    int height_right = height2(node->getRight());
    if (height_right == -1) return -1;

    if (abs(height_left - height_right) > 1) return -1;
    return height_left > height_right ?
        height_left + 1 : height_right + 1;
}

bool is_balanced2(Node* node) {
    if (!node) return true;
    return height2(node) != -1;
}

bool test_tree_one_node() {
    Node root(1, 0, 0);

    return is_balanced(&root) &&
           is_balanced2(&root);
}

bool test_tree_balanced() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node right(3, 0, 0);
    Node root(4, &left, &right);

    return is_balanced(&root) &&
           is_balanced2(&root);
}

bool test_tree_not_balanced() {
    Node leftleftleft(1, 0, 0);
    Node leftleft(2, &leftleftleft, 0);
    Node left(3, &leftleft, 0);
    Node root(4, &left, 0);

    return !is_balanced(&root) &&
           !is_balanced2(&root);
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

