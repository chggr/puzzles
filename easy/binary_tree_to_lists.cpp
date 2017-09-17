#include <iostream>
#include <list>
#include <vector>

// Task description: Given a binary tree, design an algorithm to create one
// linked list for each level, containing all the nodes at that depth.
//
// E.g. For the binary tree below it should return the following lists:
//
//                      1                  1
//                   2     3       ==>     2 => 3
//                 4   5 6   7             4 => 5 => 6 => 7
//
// Solution: The implementation below is a breadth-first algorithm to visit
// each level in turn, create the corresponding linked list and add it to the
// vector of lists. This algorithm has O(N) runtime complexity and O(1) space
// complexity.
//
// A different approach would be to use a depth-first algorithm to recursively
// visit all elements in the binary tree and add each one to the correct list.
// This approach also has O(N) runtime complexity, but its space complexity is
// O(logN) for balanced trees, as each recursion uses space in the stack.

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

vector< list<Node*> > tree_to_lists(Node* root) {

    vector< list<Node*> > results;

    list<Node*> rootList;
    if (root) {
        rootList.push_front(root);
        results.push_back(rootList);
    }

    while(!results.empty()) {
        list<Node*> previous = results.at(results.size() - 1);
        list<Node*> current;

        list<Node*>::iterator it = previous.begin();
        for (; it != previous.end(); ++it) {
            Node* left = (*it)->getLeft();
            Node* right = (*it)->getRight();

            if (right) current.push_front(right);
            if (left) current.push_front(left);
        }
        if (current.empty()) break;
        results.push_back(current);
    }
    return results;
}

bool test_one_level() {
    Node root(1, 0, 0);

    vector< list<Node*> > result = tree_to_lists(&root);
    return 1 == result.size() && 1 == result.at(0).size() &&
           1 == result.at(0).front()->getValue();
}

bool test_two_levels() {
    Node left(2, 0, 0);
    Node right(3, 0, 0);
    Node root(1, &left, &right);

    vector< list<Node*> > result = tree_to_lists(&root);
    return 2 == result.size() &&
           1 == result.at(0).size() &&
           2 == result.at(1).size() &&
           1 == result.at(0).front()->getValue() &&
           2 == result.at(1).front()->getValue() &&
           3 == result.at(1).back()->getValue();
}

bool test_three_levels() {
    Node leftleft(4, 0, 0);
    Node left(2, &leftleft, 0);
    Node right(3, 0, 0);
    Node root(1, &left, &right);

    vector< list<Node*> > result = tree_to_lists(&root);
    return 3 == result.size() &&
           1 == result.at(0).size() &&
           2 == result.at(1).size() &&
           1 == result.at(2).size() &&
           1 == result.at(0).front()->getValue() &&
           2 == result.at(1).front()->getValue() &&
           3 == result.at(1).back()->getValue() &&
           4 == result.at(2).front()->getValue();
}

int main() {
    int counter = 0;
    if (!test_one_level()) {
        cout << "One level test failed!" << endl;
        counter++;
    }
    if (!test_two_levels()) {
        cout << "Two levels test failed!" << endl;
        counter++;
    }
    if (!test_three_levels()) {
        cout << "Three levels test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

