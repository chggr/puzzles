#include <iostream>

// Task description: Implement a stack and its basic functions: push(), pop()
// and peek().

template <class T> class Stack {
    public:
        T pop();
        T peek();
        void push(T item);
        bool isEmpty();
        ~Stack();

    private:
        class Node {
            public:
                T data;
                Node* next;
        };
        Node* head = NULL;
};

template <class T> T Stack<T>::pop() {
    if (head == NULL) {
        throw std::out_of_range("Stack is empty");
    }

    T data = head->data;
    Node* next = head->next;
    delete head;
    head = next;
    return data;
}

template <class T> T Stack<T>::peek() {
    if (head == NULL) {
        throw std::out_of_range("Stack is empty");
    }
    return head->data;
}

template <class T> void Stack<T>::push(T data) {
    Node* node = new Node();
    node->data = data;
    node->next = head;
    head = node;
}

template <class T> bool Stack<T>::isEmpty() {
    return head == NULL;
}

template <class T> Stack<T>::~Stack<T>() {
    while(head != NULL) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

bool test_is_empty() {
    Stack<int> stackA;

    Stack<int> stackB;
    stackB.push(1);
    stackB.push(2);

    return stackA.isEmpty() && !stackB.isEmpty();
}

bool test_push_pop() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    return !stack.isEmpty() && 2 == stack.pop() &&
           1 == stack.pop() && stack.isEmpty();
}

bool test_pop_empty() {
    Stack<int> stack;

    try {
        stack.pop();
    } catch (std::out_of_range e) {
        return true;
    }
    return false;
}

bool test_peek() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    return 2 == stack.peek() && 2 == stack.pop() &&
           1 == stack.peek() && 1 == stack.pop() &&
           stack.isEmpty();
}

bool test_peek_empty() {
    Stack<int> stack;

    try {
        stack.peek();
    } catch (std::out_of_range e) {
        return true;
    }
    return false;
}

int main() {
    int counter = 0;
    if (!test_is_empty()) {
        std::cout << "Is empty test failed!" << std::endl;
        counter++;
    }
    if (!test_push_pop()) {
        std::cout << "Push pop test failed!" << std::endl;
        counter++;
    }
    if (!test_pop_empty()) {
        std::cout << "Pop empty test failed!" << std::endl;
        counter++;
    }
    if (!test_peek()) {
        std::cout << "Peek test failed!" << std::endl;
        counter++;
    }
    if (!test_peek_empty()) {
        std::cout << "Peek empty test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

