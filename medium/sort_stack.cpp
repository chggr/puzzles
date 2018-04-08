#include <iostream>
#include <stack>

// Task description: Given a stack, write a method to sort it so that the
// smallest items are on top. Only an additional temporary stack can be used,
// the elements should not be copied into any other data structure.
//
// Solution: In the implementation below, a temporary stack is used to store
// elements in the reverse order than required (i.e. from largest to smallest).
// The elements in the temporary stack will be popped and transferred to the
// main stack to obtain the correct order.
//
// In every iteration, one element is popped from the main stack and compared
// to the top element of the temporary stack. If it is greater or equal, the
// element is simply pushed in the temporary stack. If it is smaller, it needs
// to be pushed deeper inside the temporary stack. Therefore the temporary
// stack is unrolled onto the main stack until the correct position is found
// and the element is inserted. The space complexity of this algorithm is O(N)
// and time complexity is O(N^2).

void sort(std::stack<int> &stack) {

    std::stack<int> temp;
    while(!stack.empty()) {
        int value = stack.top();
        stack.pop();

        if (temp.empty() || value >= temp.top()) {
            temp.push(value);
        } else {
            while (!temp.empty() && temp.top() > value) {
                stack.push(temp.top());
                temp.pop();
            }
            temp.push(value);
        }
    }

    while (!temp.empty()) {
        stack.push(temp.top());
        temp.pop();
    }
}

int pop(std::stack<int> &stack) {
    int value = stack.top();
    stack.pop();
    return value;
}

bool test_sort_empty() {
    std::stack<int> stack;
    sort(stack);
    return 0 == stack.size();
}

bool test_sort_already_sorted() {
    std::stack<int> stack;
    stack.push(3);
    stack.push(2);
    stack.push(1);

    sort(stack);
    return 3 == stack.size() && 1 == pop(stack) &&
           2 == pop(stack) && 3 == pop(stack);
}

bool test_sort() {
    std::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    sort(stack);
    return 3 == stack.size() && 1 == pop(stack) &&
           2 == pop(stack) && 3 == pop(stack);
}

int main() {
    int counter = 0;
    if (!test_sort_empty()) {
        std::cout << "Empty stack sort test failed!" << std::endl;
        counter++;
    }
    if (!test_sort_already_sorted()) {
        std::cout << "Already sorted stack sort test failed!" << std::endl;
        counter++;
    }
    if (!test_sort()) {
        std::cout << "Stack sort test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

