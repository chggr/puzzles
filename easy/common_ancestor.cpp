#include <iostream>

// Task description: Given the root node and two other nodes of a binary tree,
// design an algorithm that will identify the first common ancestor of the
// given nodes.
//
// Solution: This task involves a binary tree and not a binary search tree. If
// this was a binary search tree, the solution would be to create a custom find
// operation for the two nodes and check where the paths in the tree diverge.
// For a simple binary tree the solution will need to be a bit more elaborate.
//
// The implementation below begins from the root node and moves through the
// tree until a common ancestor of the given nodes x and y is found. For each
// node, it checks if both x and y are on the same side, i.e. whether both x
// and y are on the left subtree or the right subtree. If indeed they are on
// the same subtree, it branches towards that subtree to continue searching.
// On the contrary if they are on different subtrees, then the current node is
// the first common ancestor. The runtime complexity of this algorithm is O(N)
// on a balanced tree, which is the best complexity that can be achieved since
// we need to potentially look at every node in the tree.
//
// A different algorithm could be applied if each tree node also had a pointer
// to its parent. In this case we would start from one of the given nodes, move
// upwards and in each iteration check whether the other subtree contains the
// second node.

class Node {

    private:
        int value;
        Node* left;
        Node* right;

    public:
        Node(int value, Node* left, Node* right) :
            value(value), left(left), right(right) { }
        int getValue() const { return value; }
        Node* getLeft() const { return left; }
        Node* getRight() const { return right; }
};

bool is_ancestor(Node* ancestor, Node* node) {
    if (ancestor == 0) return false;
    if (ancestor == node) return true;

    return is_ancestor(ancestor->getLeft(), node) ||
           is_ancestor(ancestor->getRight(), node);
}

Node* common_ancestor(Node* root, Node* x, Node* y) {
    if (!is_ancestor(root, x) || !is_ancestor(root, y)) {
        throw "One or both nodes do not exist in the tree.";
    }

    Node* current = root;
    while(current) {
        bool left_x = is_ancestor(current->getLeft(), x);
        bool left_y = is_ancestor(current->getLeft(), y);
        if (left_x != left_y) return current;
        current = left_x ? current->getLeft() : current->getRight();
    }
    return 0;
}

bool test_first_node_missing() {
    Node x(1, 0, 0);
    Node y(2, 0, 0);
    Node root(3, 0, &y);

    try {
        common_ancestor(&root, &x, &y);
        return false;
    } catch (const char* message) {
        return true;
    }
}

bool test_second_node_missing() {
    Node x(1, 0, 0);
    Node y(2, 0, 0);
    Node root(3, &x, 0);

    try {
        common_ancestor(&root, &x, &y);
        return false;
    } catch (const char* message) {
        return true;
    }
}

bool test_node_is_parent() {
    Node x(1, 0, 0);
    Node y(2, &x, 0);
    Node root(3, &y, 0);

    return &y == common_ancestor(&root, &x, &y);
}

bool test_common_ancestor() {
    Node x(1, 0, 0);
    Node y(2, 0, 0);
    Node left(3, &x, 0);
    Node right(4, 0, &y);
    Node root(5, &left, &right);

    return &root == common_ancestor(&root, &x, &y);
}

int main() {
    int counter = 0;
    if (!test_first_node_missing()) {
        std::cout << "First node missing test failed!" << std::endl;
        counter++;
    }
    if (!test_second_node_missing()) {
        std::cout << "Second node missing test failed!" << std::endl;
        counter++;
    }
    if (!test_node_is_parent()) {
        std::cout << "One node is parent of the other test failed!" << std::endl;
        counter++;
    }
    if (!test_common_ancestor()) {
        std::cout << "Common ancestor test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

