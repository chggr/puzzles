#include <iostream>

// Task description: Create a priority queue using a binary max-heap so that we
// can push integers in the queue and pop the largest one, i.e. the one with
// maximum priority. Use an array to implement the binary heap. What is the
// runtime complexity of push() and pop()?
//
// Solution: Priority queues are typically implemented using min or max binary
// heaps. These are binary trees with two additional constraints:
//
// (1) A binary heap is a complete binary tree, i.e. all levels of the tree are
//     fully populated except possibly the deepest one. As new elements are
//     added, the nodes of the deepest level are filled from left to right.
//
// (2) The key stored in each node is either greater than or equal (max-heap) or
//     less than or equal (min-heap) compared to the keys of its children.
//
// Both push() and pop() operations take O(logn) time and initially modify the
// heap to conform to the first property. Then they use upheap() and downheap()
// operations respectively to establish the second property as well.Upheap()
// bubbles an element from the deepest level upwards by comparing it to its
// parent and swapping them if necessary. On the contrary downheap() bubbles the
// root element down by comparing it to both its children and swapping it with
// the largest child if required.
//
// Heaps are commonly implemented using an array as the underlying data
// structure, where the root node is stored at position zero. The children for
// any node are stored at indices 2*i + 1 and 2*i + 2, whereas the parent at
// index floor((i - 1) / 2). A binary heap can also be implemented using a
// traditional binary tree data structure, but in this case it is much harder
// to identify the adjacent node on the last level when adding a new element.
// This can be done either algorithmically or by adding extra data to the nodes,
// but in any case is less performant than an array.

class PriorityQueue {

    private:
        int *array;
        int size;
        int current;

        void swap(int a, int b);
        void upheap(int child);
        void downheap(int parent);

    public:
        PriorityQueue(int capacity);
        ~PriorityQueue();
        void push(int value);
        int pop();
};

void PriorityQueue::swap(int a, int b) {
    if (a == b) return;
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Bubbles up a child if greater than its parent.
void PriorityQueue::upheap(int child) {
    int parent = (child - 1) / 2;
    if (array[child] > array[parent]) {
        swap(parent, child);
        upheap(parent);
    }
}

// Bubbles down a parent if smaller than its children.
void PriorityQueue::downheap(int parent) {
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;
    int max = parent;

    if (left < current && array[left] > array[max]) max = left;
    if (right < current && array[right] > array[max]) max = right;

    if (max != parent) {
        swap(parent, max);
        downheap(max);
    }
}

PriorityQueue::PriorityQueue(int capacity) {
    array = new int[capacity];
    size = capacity;
    current = 0;
}

PriorityQueue::~PriorityQueue() {
    delete array;
}

// Adds the new value at the deepest level of the tree and
// bubbles it up if necessary.
void PriorityQueue::push(int value) {
    if (current >= size) return;

    array[current] = value;
    upheap(current);
    current++;
}

// Removes and returns the root. The last element is placed
// at the root and is bubbled down as necessary.
int PriorityQueue::pop() {
    if (current == 0) return -1;

    int root = array[0];
    current--;
    array[0] = array[current];
    downheap(0);
    return root;
}

bool test_pop_empty() {
    PriorityQueue queue(10);
    return -1 == queue.pop();
}

bool test_push_full() {
    PriorityQueue queue(10);
    for (int i = 0; i < 100; i++) {
        queue.push(i);
    }
    return 9 == queue.pop();
}

bool test_push_pop() {
    PriorityQueue queue(10);
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }

    for (int i = 9; i >= 0; i--) {
        if (queue.pop() != i) return false;
    }
    return true;
}

int main() {
    int counter = 0;
    if (!test_pop_empty()) {
        std::cout << "Pop empty queue test failed!" << std::endl;
        counter++;
    }
    if (!test_push_full()) {
        std::cout << "Push full queue test failed!" << std::endl;
        counter++;
    }
    if (!test_push_pop()) {
        std::cout << "Push pop queue test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

