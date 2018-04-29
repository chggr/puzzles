#include <iostream>
#include <stack>

// Task description: Write a class to stream a binary search tree in sorted
// order using at most O(logN) storage, where N is the total number of nodes in
// the tree.
//                                             3
// E.g. for binary search tree:             2    5
//                                        1    4   6
//
//      the stream should consist of: 1 => 2 => 3 => 4 => 5 => 6
//
// Solution: The implementation below basically performs in-order traversal of
// the given tree iteratively, using an external stack to store any unvisited
// nodes. It initially pushes the root node along with all nodes at its left.
// As soon as an element is popped, its right sub-tree is added to the stack.
// Given two BSTs this class allows us to merge them in O(N + M) time and
// O(logM + logN) space.

using namespace std;

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

class TreeStream {

    private:
        stack<Node*> s;

        void add(Node* node) {
            while (node != NULL) {
                s.push(node);
                node = node->getLeft();
            }
        }

    public:
        TreeStream(Node* root) {
            add(root);
        }

        Node* top() {
            return s.empty() ? NULL : s.top();
        }

        bool pop() {
            if (s.empty()) return false;

            Node* temp = s.top();
            s.pop();
            add(temp->getRight());
            return true;
        }
};

bool test_empty() {
    TreeStream stream(NULL);
    return NULL == stream.top() && !stream.pop();
}

bool test_single() {
    Node root(1, NULL, NULL);
    TreeStream stream(&root);
    return &root == stream.top() && stream.pop() &&
           NULL == stream.top() && !stream.pop();
}

bool test_tree() {
    Node leftleft(1, NULL, NULL);
    Node left(2, &leftleft, NULL);
    Node rightleft(4, NULL, NULL);
    Node rightright(6, NULL, NULL);
    Node right(5, &rightleft, &rightright);
    Node root(3, &left, &right);

    TreeStream stream(&root);
    return 1 == stream.top()->getValue() && stream.pop() &&
           2 == stream.top()->getValue() && stream.pop() &&
           3 == stream.top()->getValue() && stream.pop() &&
           4 == stream.top()->getValue() && stream.pop() &&
           5 == stream.top()->getValue() && stream.pop() &&
           6 == stream.top()->getValue() && stream.pop() &&
           NULL == stream.top() && !stream.pop();
}

int main() {
    int counter = 0;
    if (!test_empty()) {
        std::cout << "Empty stream test failed!" << std::endl;
        counter++;
    }
    if (!test_single()) {
        std::cout << "Single node stream test failed!" << std::endl;
        counter++;
    }
    if (!test_tree()) {
        std::cout << "Tree stream test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

