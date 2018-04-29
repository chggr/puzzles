#include <iostream>

// Task description: Given two binary search trees, write a method to merge them
// into one binary search tree.
//
// Solution: One approach to merge two binary search trees would be to insert
// all nodes of the first BST into the second BST. The runtime complexity in
// this case would be O(M * log(M + N)) where M and N are the number of nodes in
// the first and second BST respectively. As an optimization we could choose to
// merge the smaller tree into the larger one.
//
// The implementation below is more efficient and merges the two trees by first
// flattening them out into two arrays, merging the arrays into one and then
// reinflating the array into a BST. The runtime complexity of each of these
// operations is as follows, which gives an overall runtime complexity of this
// algorithm equal to O(N + M).
//
// - Flatten first BST: O(N)
// - Flatten second BST: O(M)
// - Merge two arrays: O(N + M)
// - Inflate final BST: O(N + M)

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

// Counts the number of nodes in a tree.
int node_count(Node* root) {
    if (root == NULL) return 0;
    return 1 + node_count(root->getLeft())
             + node_count(root->getRight());
}

// Flattens a tree into an array.
void flatten(Node* root, int array[], int& pos) {
    if (root == NULL) return;
    flatten(root->getLeft(), array, pos);
    array[pos++] = root->getValue();
    flatten(root->getRight(), array, pos);
}

// Merges two sorted arrays into a third sorted array.
void merge(int a[], int a_size, int b[], int b_size, int c[]) {
    int a_idx = 0;
    int b_idx = 0;
    int c_idx = 0;

    while (c_idx < a_size + b_size) {
        if (a_idx >= a_size) {
            c[c_idx++] = b[b_idx++];
            continue;
        }
        if (b_idx >= b_size) {
            c[c_idx++] = a[a_idx++];
            continue;
        }
        c[c_idx++] = a[a_idx] < b[b_idx] ?
            a[a_idx++] : b[b_idx++];
    }
}

// Inflates a sorted array into a binary search tree.
Node* inflate(int array[], int from, int to) {
    if (from > to) return NULL;
    if (from == to) return new Node(array[from], NULL, NULL);

    int mid = (from + to) / 2;
    Node* left = inflate(array, from, mid - 1);
    Node* right = inflate(array, mid + 1, to);
    return new Node(array[mid], left, right);
}

// Merges two binary search trees into one.
Node* merge (Node* a, Node* b) {
    int a_count = node_count(a);
    int a_values[a_count];
    int a_index = 0;
    flatten(a, a_values, a_index);

    int b_count = node_count(b);
    int b_values[b_count];
    int b_index = 0;
    flatten(b, b_values, b_index);

    int c_values[a_count + b_count];
    merge(a_values, a_count, b_values, b_count, c_values);
    return inflate(c_values, 0, a_count + b_count - 1);
}

bool assert(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void delete_tree(Node* root) {
    if (root == NULL) return;
    delete_tree(root->getLeft());
    delete_tree(root->getRight());
    delete root;
}

bool test_node_count() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node rightleft(4, 0, 0);
    Node rightright(6, 0, 0);
    Node right(5, &rightleft, &rightright);
    Node root(3, &left, &right);
    return 6 == node_count(&root);
}

bool test_flatten() {
    Node leftleft(1, 0, 0);
    Node left(2, &leftleft, 0);
    Node rightleft(4, 0, 0);
    Node rightright(6, 0, 0);
    Node right(5, &rightleft, &rightright);
    Node root(3, &left, &right);

    int result[6];
    int expected[] = {1, 2, 3, 4, 5, 6};
    int index = 0;
    flatten(&root, result, index);
    return assert(result, expected, 6);
}

bool test_merge() {
    int a[] = {1, 4, 7, 9};
    int b[] = {2, 3, 5, 6, 8};

    int result[9];
    merge(a, 4, b, 5, result);
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return assert(result, expected, 9);
}

bool test_inflate() {
    int array[] = {1, 2, 3, 4, 5};
    Node* root = inflate(array, 0, 4);

    int result[5];
    int index = 0;
    flatten(root, result, index);

    delete_tree(root);
    return assert(array, result, 5);
}

bool test_merge_bst() {
    int a[] = {1, 4, 7, 9};
    Node* a_tree = inflate(a, 0, 3);

    int b[] = {2, 3, 5, 6, 8};
    Node* b_tree = inflate(b, 0, 4);

    Node* m_tree = merge(a_tree, b_tree);
    int result[9];
    int index = 0;
    flatten(m_tree, result, index);

    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return assert(result, expected, 9);
}

int main() {
    int counter = 0;
    if (!test_node_count()) {
        counter++;
        std::cout << "Node count test failed!" << std::endl;
    }
    if (!test_flatten()) {
        counter++;
        std::cout << "Flatten test failed!" << std::endl;
    }
    if (!test_merge()) {
        counter++;
        std::cout << "Merge test failed!" << std::endl;
    }
    if (!test_inflate()) {
        counter++;
        std::cout << "Inflate test failed!" << std::endl;
    }
    if (!test_merge_bst()) {
        counter++;
        std::cout << "Merge two BSTs test failed!" << std::endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

