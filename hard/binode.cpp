#include <iostream>

// Task description: Consider a simple data structure called BiNode that
// contains pointers to two other nodes. This data structure can be used to
// represent a binary tree, where one pointer is the left subtree and the other
// is the right subtree. It can also be used to represent a doubly linked list,
// where one pointer is the previous element and the other pointer the next.
// Implement a method to convert a binary search tree implemented with BiNodes
// int a doubly linked list. The values should be kept in order and the
// operation should be performed in place.
//
// Solution: The implementation below uses recursion to transform the binary
// search tree into a doubly linked list. The recursive method first transforms
// the left part into a list and links its tail to the root. It then transforms
// the right part and links its head to the root. Finally it returns the head
// of the transformed list. The runtime complexity of this approach is O(n^2)
// because each leaf node at depth D will be touched by method get_tail D times,
// once for every node above it.

class BiNode {

    private:
        int value;
        BiNode* left;
        BiNode* right;

    public:
        BiNode(int value, BiNode* left, BiNode* right) :
            value(value), left(left), right(right) { };
        int getValue() { return value; }
        BiNode* getLeft() { return left; }
        void setLeft(BiNode* node) { left = node; }
        BiNode* getRight() { return right; }
        void setRight(BiNode* node) { right = node; }
};

BiNode* get_tail(BiNode* root) {
    if (root == NULL) return NULL;

    BiNode* tail = root;
    while (tail->getRight()) {
        tail = tail->getRight();
    }
    return tail;
}

BiNode* transform(BiNode* root) {
    if (root == NULL) return NULL;

    BiNode* left_part = transform(root->getLeft());
    if (left_part != NULL) {
        BiNode* tail = get_tail(left_part);
        root->setLeft(tail);
        tail->setRight(root);
    }

    BiNode* right_part = transform(root->getRight());
    if (right_part) {
        root->setRight(right_part);
        right_part->setLeft(root);
    }

    return left_part == NULL ? root : left_part;
}

bool assert_list(int array[], int size, BiNode* list) {
    for (int i = 0; i < size; i++) {
        if (list->getValue() != array[i]) {
            return false;
        }
        list = list->getRight();
    }
    return list == NULL;
}

bool test_only_root() {
    BiNode root(1, NULL, NULL);

    BiNode* result = transform(&root);
    int expected[] = { 1 };
    return assert_list(expected, 1, result);
}

bool test_one_node_left() {
    BiNode left(1, NULL, NULL);
    BiNode root(2, &left, NULL);

    BiNode* result = transform(&root);
    int expected[] = { 1, 2 };
    return assert_list(expected, 2, result);
}

bool test_one_node_right() {
    BiNode right(2, NULL, NULL);
    BiNode root(1, NULL, &right);

    BiNode* result = transform(&root);
    int expected[] = { 1, 2 };
    return assert_list(expected, 2, result);
}

bool test_three_nodes() {
    BiNode left(1, NULL, NULL);
    BiNode right(3, NULL, NULL);
    BiNode root(2, &left, &right);

    BiNode* result = transform(&root);
    int expected[] = { 1, 2, 3 };
    return assert_list(expected, 3, result);
}

bool test_full_tree() {
    BiNode leftleft(1, NULL, NULL);
    BiNode leftright(3, NULL, NULL);
    BiNode left(2, &leftleft, &leftright);

    BiNode rightleft(5, NULL, NULL);
    BiNode rightright(7, NULL, NULL);
    BiNode right(6, &rightleft, &rightright);

    BiNode root(4, &left, &right);

    BiNode* result = transform(&root);
    int expected[] = { 1, 2, 3, 4, 5, 6, 7 };
    return assert_list(expected, 7, result);
}

int main() {
    int counter = 0;
    if (!test_only_root()) {
        std::cout << "Only root test failed!" << std::endl;
        counter++;
    }
    if (!test_one_node_left()) {
        std::cout << "One node left test failed!" << std::endl;
        counter++;
    }
    if (!test_one_node_right()) {
        std::cout << "One node right test failed!" << std::endl;
        counter++;
    }
    if (!test_three_nodes()) {
        std::cout << "Three nodes test failed!" << std::endl;
        counter++;
    }
    if (!test_full_tree()) {
        std::cout << "Full tree test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

