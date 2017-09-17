#include<iostream>

// Task description: Given a node in a binary search tree, implement a method
// to find and return the "next" node (its in-order successor). Each tree node
// also has a link to its parent.
//
// E.g. For the binary search tree below:
//
//           4            The successor of node 1 is node 2.
//        2     6         The successor of node 3 is node 4.
//       1 3   5 7        The successor of node 7 is null.
//
// Solution: A binary search tree can be traversed in order if we first visit
// the left subtree, then the current node and then the right subtree. This is
// the basis of the algorithm implemented below. In summary there are three
// possible scenaria that need to be covered:
//
// 1) If the node has a right subtree, the successor will be the leftmost node
//    in the right subtree.
//
// 2) If the value of the parent is greater that the value of the node, it
//    means that the node is on the left side of the parent, thus the parent is
//    the successor.
//
// 3) If the value of the parent is less than the value of the node, it means
//    that the node is on the right side of the parent. Therefore we need to
//    move upwards the tree until we find a parent whose value will be greater
//    than that of the node. That parent will be the succesor.
//
// 4) If all steps above have not yielded a successor, it means that the node
//    is the rightmost node in the tree and does not have a successor at all.

class Node {

    private:
        Node* parent;
        Node* left;
        Node* right;
        int value;

    public:
        Node(int value, Node* left, Node* right) :
            value(value), left(left), right(right) { }
        Node* getRight() { return right; }
        Node* getLeft() { return left; }
        int getValue() { return value; }
        void setParent(Node* p) { parent = p; }
        Node* getParent() { return parent; }
};

Node* get_successor(Node* node) {
    if (!node) return 0;

    if (node->getRight()) {
        Node* temp = node->getRight();
        while (temp->getLeft()) {
            temp = temp->getLeft();
        }
        return temp;
    }

    Node* parent = node->getParent();
    while(parent) {
        if (parent->getValue() > node->getValue()) {
            return parent;
        }
        parent = parent->getParent();
    }
    return 0;
}

bool test_null_node() {
    return 0 == get_successor(0);
}

bool test_successor() {
    Node leftleft(1, 0, 0);
    Node leftright(3, 0, 0);
    Node left(2, &leftleft, &leftright);
    leftleft.setParent(&left);
    leftright.setParent(&left);

    Node rightleft(5, 0, 0);
    Node rightright(7, 0, 0);
    Node right(6, &rightleft, &rightright);
    rightleft.setParent(&right);
    rightright.setParent(&right);

    Node root(4, &left, &right);
    right.setParent(&root);
    left.setParent(&root);
    root.setParent(0);

    return &left == get_successor(&leftleft) &&
           &leftright == get_successor(&left) &&
           &root == get_successor(&leftright) &&
           &rightleft == get_successor(&root) &&
           &right == get_successor(&rightleft) &&
           &rightright == get_successor(&right) &&
           0 == get_successor(&rightright);
}

int main() {
    int counter = 0;
    if (!test_null_node()) {
        std::cout << "Null node test failed!" << std::endl;
        counter++;
    }
    if (!test_successor()) {
        std::cout << "Successor test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

