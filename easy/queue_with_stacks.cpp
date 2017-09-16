#include <iostream>
#include <stack>

// Task description: Implement a queue using only stacks.
//
// Solution: The major difference between a queue and a stack is the order
// in which the elements are retrieved (FIFO and LIFO). Two stacks can be used
// to implement a queue: a "head" stack where all new elements will be inserted
// into and a "tail" stack where elements will be removed from. When the "tail"
// stack is empty, all elements from the "head" stack will be popped and
// inserted into the "tail" stack. This approach achieves FIFO behaviour.

class QueueWithStacks {

    private:
        std::stack<int> head;
        std::stack<int> tail;

    public:
        int remove();
        void add(int value);
        bool empty();
        int size();
};

int QueueWithStacks::remove() {
    if (empty()) {
        throw "Queue is empty";
    }

    if (tail.empty()) {
        while(!head.empty()) {
            tail.push(head.top());
            head.pop();
        }
    }
    int value = tail.top();
    tail.pop();
    return value;
}

void QueueWithStacks::add(int value) {
    head.push(value);
}

bool QueueWithStacks::empty() {
    return head.empty() && tail.empty();
}

int QueueWithStacks::size() {
    return head.size() + tail.size();
}

bool test_queue_empty() {
    QueueWithStacks queue;
    return queue.empty();
}

bool test_queue_remove_empty() {
    QueueWithStacks queue;
    try {
        queue.remove();
        return false;
    } catch (const char* message) {
        return true;
    }
}

bool test_queue_remove() {
    QueueWithStacks queue;
    queue.add(1);
    queue.add(2);
    queue.add(3);

    return 1 == queue.remove() && 2 == queue.remove() &&
           3 == queue.remove() && queue.empty();
}

bool test_queue_size() {
    QueueWithStacks queue;
    queue.add(1);

    return 1 == queue.size() && 1 == queue.remove() &&
           0 == queue.size();
}

int main() {
    int counter = 0;
    if (!test_queue_empty()) {
        std::cout << "Empty queue test failed!" << std::endl;
        counter++;
    }
    if (!test_queue_remove_empty()) {
        std::cout << "Remove on empty queue test failed!" << std::endl;
        counter++;
    }
    if (!test_queue_remove()) {
        std::cout << "Queue remove test failed!" << std::endl;
        counter++;
    }
    if (!test_queue_size()) {
        std::cout << "Queue size test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

