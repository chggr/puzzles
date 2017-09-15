#include <iostream>
#include <stack>

// Task description: Implement a data structure SetOfStacks that is composed of
// many individual stacks. A new stack should be created when the previous one
// has reached the given maximum capacity. The class should expose methods
// push() and pop() that behave identically like having a single stack.
// Additionally, implement a function popAt(int index) which performs a pop
// operation on a given sub-stack.

class SetOfStacks {
    private:
        std::stack< std::stack<int> > stacks;
        int maxCapacity;

    public:
        SetOfStacks(int capacity);
        int pop();
        int popAt(int index);
        bool empty();
        void push(int value);
};

SetOfStacks::SetOfStacks(int capacity) {
    maxCapacity = capacity;
}

int SetOfStacks::pop() {
    if (stacks.empty()) {
        throw "Stack is empty";
    }

    int value = stacks.top().top();
    stacks.top().pop();
    if (stacks.top().empty()) {
        stacks.pop();
    }
    return value;
}

int SetOfStacks::popAt(int index) {
    std::stack< std::stack<int> > temp;
    while (index > 0 && !stacks.empty()) {
        temp.push(stacks.top());
        stacks.pop();
        index--;
    }

    if (index > 0 || stacks.empty()) {
        while(!temp.empty()) {
            stacks.push(temp.top());
            temp.pop();
        }
        throw "Index too large";
    }

    int value = stacks.top().top();
    stacks.top().pop();
    while(!temp.empty()) {
        stacks.push(temp.top());
        temp.pop();
    }
    return value;
}

bool SetOfStacks::empty() {
    return stacks.empty();
}

void SetOfStacks::push(int value) {
    if (stacks.empty() || stacks.top().size() == maxCapacity) {
        std::stack<int> newStack;
        stacks.push(newStack);
    }
    stacks.top().push(value);
}

bool test_stacks_empty() {
    SetOfStacks stacks(2);
    return stacks.empty();
}

bool test_pop_empty_stacks() {
    SetOfStacks stacks(2);
    try {
        stacks.pop();
        return false;
    } catch (const char* message) {
        return true;
    }
}

bool test_pop() {
    SetOfStacks stacks(2);
    stacks.push(1);
    stacks.push(2);
    stacks.push(3);
    stacks.push(4);

    return 4 == stacks.pop() && 3 == stacks.pop() &&
           2 == stacks.pop() && 1 == stacks.pop() &&
           stacks.empty();
}

bool test_pop_at() {
    SetOfStacks stacks(2);
    stacks.push(1);
    stacks.push(2);
    stacks.push(3);
    stacks.push(4);

    return 2 == stacks.popAt(1) && 4 == stacks.pop() &&
           3 == stacks.pop() && 1 == stacks.pop() &&
           stacks.empty();
}

bool test_pop_at_large_index() {
    SetOfStacks stacks(2);
    stacks.push(1);
    stacks.push(2);
    stacks.push(3);

    try {
        stacks.popAt(100);
        return false;
    } catch (const char* message) {
        return true;
    }
}

int main() {
    int counter = 0;
    if (!test_stacks_empty()) {
        std::cout << "Empty stacks test failed!" << std::endl;
        counter++;
    }
    if (!test_pop_empty_stacks()) {
        std::cout << "Pop empty stacks test failed!" << std::endl;
        counter++;
    }
    if (!test_pop()) {
        std::cout << "Pop test failed!" << std::endl;
        counter++;
    }
    if (!test_pop_at()) {
        std::cout << "Pop at test failed!" << std::endl;
        counter++;
    }
    if (!test_pop_at_large_index()) {
        std::cout << "Pop at with large index test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

