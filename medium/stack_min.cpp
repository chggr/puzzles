#include <iostream>
#include <stack>
#include <stdexcept>

// Task description: Design a stack that in addition to push() and pop() also
// has a min() function to return the minimum element currently in the stack.
// All operations (push, pop, min) should have an O(1) runtime complexity.
//
// E.g. For stack 9 => 1 => 8, min() should return 1 and pop() should return 9
//
// Solution: The most straight forward solution to this problem is to have just
// a single variable "minValue" that will hold the minimum element in the stack.
// When minValue is popped from the stack, we search through the stack to find
// the new minimum. Although we might expect this not to happen very often, it
// still breaks the task's constraint that all operations should have O(1)
// runtime complexity.
//
// An alternative solution would be to store the minimum value as part of each
// node of the stack. Therefore each node will have the minimum value of all
// elements beneath itself. This helps keep track of the minimum at each state
// and enables us to return the minimum value in O(1). Unfortunately though
// this solution is very costly for large stacks, as a lot of space is wasted
// by keeping track of the minimum for every single element.
//
// A better solution would be to maintain two separate stacks, one "main" stack
// to hold all elements and a secondary "mins" stack to hold all the minimum
// values. The implementation bellow follows this approach.

class StackMin {
    private:
        std::stack<int> mins;
        std::stack<int> main;

    public:
        int pop();
        int min();
        bool empty();
        void push(int value);
};

int StackMin::pop() {
    if (main.empty()) {
        throw "Stack is empty";
    }

    int value = main.top();
    main.pop();
    if (value == mins.top()) {
        mins.pop();
    }
    return value;
}

int StackMin::min() {
    if (mins.empty()) {
        throw "Stack is empty";
    }
    return mins.top();
}

void StackMin::push(int value) {
    if (mins.empty() || value <= mins.top()) {
        mins.push(value);
    }
    main.push(value);
}

bool StackMin::empty() {
    return main.empty();
}

bool test_stack_one_element() {
    StackMin stack;
    stack.push(1);
    return 1 == stack.min() && 1 == stack.pop() && stack.empty();
}

bool test_stack_unique_elements() {
    StackMin stack;
    stack.push(8);
    stack.push(1);
    stack.push(9);

    return 1 == stack.min() && 9 == stack.pop() &&
           1 == stack.min() && 1 == stack.pop() &&
           8 == stack.min() && 8 == stack.pop() &&
           stack.empty();
}

bool test_stack_duplicate_elements() {
    StackMin stack;
    stack.push(1);
    stack.push(8);
    stack.push(1);

    return 1 == stack.min() && 1 == stack.pop() &&
           1 == stack.min() && 8 == stack.pop() &&
           1 == stack.min() && 1 == stack.pop() &&
           stack.empty();
}

bool test_stack_pop_empty() {
    StackMin stack;

    try {
        stack.pop();
        return false;
    } catch (const char* message) {
        return true;
    }
}

bool test_stack_min_empty() {
    StackMin stack;

    try {
        stack.min();
        return false;
    } catch (const char* message) {
        return true;
    }
}

int main() {
    int counter = 0;
    if (!test_stack_one_element()) {
        std::cout << "Stack with one element test failed!" << std::endl;
        counter++;
    }
    if (!test_stack_unique_elements()) {
        std::cout << "Stack with unique elements test failed!" << std::endl;
        counter++;
    }
    if (!test_stack_duplicate_elements()) {
        std::cout << "Stack with duplicate elements test failed!" << std::endl;
        counter++;
    }
    if (!test_stack_pop_empty()) {
        std::cout << "Pop on empty stack test failed!" << std::endl;
        counter++;
    }
    if (!test_stack_min_empty()) {
        std::cout << "Min on empty stack test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

