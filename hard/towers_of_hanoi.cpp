#include <iostream>
#include <stack>

// Task description: In the classic problem of the Towers of Hanoi you have
// three towers and N disks of different sizes sitting arranged from smallest
// to largest on the first tower. The goal is to move all disks from the first
// to the third tower, observing the following rules:
//
// (1) Move only one disk at a time.
// (2) Do not place a disk on top of a smaller disk.
//
// Write a program to move all disks from tower one to tower three. Each tower
// can be represented as a stack of disks.
//
//E.g.          Before                                   After
//        A            B       C              A        B            C
//        |            |       |              |        |            |
//       [|]           |       |              |        |           [|]
//      [ | ]          |       |              |        |          [ | ]
//     [  |  ]         |       |              |        |         [  |  ]
//    [   |   ]        |       |              |        |        [   |   ]
//   [    |    ]       |       |              |        |       [    |    ]
//
// Solution: The implementation below is a simple recursive solution to the
// Towers of Hanoi problem. The base case is for n = 1, where only one disk
// needs to move from tower A to tower C. Every other case (n > 1) can be
// deconstructed by first moving n - 1 disks from tower A to tower B, then
// moving disk n to tower C and finally moving the n - 1 disks from tower B
// to tower C.
//
// The second implementation below solves the Towers of Hanoi problem
// iteratively, executing a total of 2^n - 1 number of steps, where n is the
// total number of disks. In every step, it makes the legal move between two
// poles, which differ in case n is even or odd. The end result is the same as
// in the recursive algorithm, but the space complexity stays at O(1).

using namespace std;

int pop(stack<int> &from) {
    int value = from.top();
    from.pop();
    return value;
}

// Moves one element from one stack to the other.
void move(stack<int> &from, stack<int> &to) {
    if (!to.empty() && from.top() > to.top()) {
       throw "Cannot place disk on top of a smaller disk.";
    }
    to.push(pop(from));
}

// Moves n elements from stack A to stack C, using stack B as buffer.
void move(stack<int> &a, stack<int> &b, stack<int> &c, int n) {
    if (a.size() < n) {
        throw "Tower A does not have enough disks.";
    }

    if (n == 1) {
        move(a, c);
        return;
    }

    // Move n - 1 elements from a to b, then the nth element from a to c and
    // finally the n - 1 elements from b to c.
    move(a, c, b, n - 1);
    move(a, c);
    move(b, a, c, n - 1);
}

// Moves the smallest disk of any tower to the other tower.
void swap(stack<int> &a, stack<int> &b) {
    if (a.empty() && b.empty()) {
        throw "Both towers empty, cannot swap disk.";
    }

    if (a.empty()) {
        move(b, a);
    } else if (b.empty()) {
        move(a, b);
    } else {
        if (a.top() > b.top()) {
            move(b, a);
        } else {
            move(a, b);
        }
    }
}

void move_it(stack<int> &a, stack<int> &b, stack<int> &c, int n) {
    if (n % 2 == 0) {
        for (int i = 0; i < (1 << n) - 1; i++) {
            if (i % 3 == 0) swap(a, b);
            else if (i % 3 == 1) swap(a, c);
            else swap(b, c);
        }
    } else {
        for (int i = 0; i < (1 << n) - 1; i++) {
            if (i % 3 == 0) swap(a, c);
            else if (i % 3 == 1) swap(a, b);
            else swap(b, c);
        }
    }
}

bool test_one_disk(bool iterative) {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(1);

    if (iterative) move_it(a, b, c, 1);
    else move(a, b, c, 1);
    return a.empty() && b.empty() && c.size() == 1 && c.top() == 1;
}

bool test_two_disks(bool iterative) {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(2);
    a.push(1);

    if (iterative) move_it(a, b, c, 2);
    else move(a, b, c, 2);
    return a.empty() && b.empty() && c.size() == 2 &&
           pop(c) == 1 && pop(c) == 2;
}

bool test_three_disks(bool iterative) {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(3);
    a.push(2);
    a.push(1);

    if (iterative) move_it(a, b, c, 3);
    else move(a, b, c, 3);
    return a.empty() && b.empty() && c.size() == 3 &&
           pop(c) == 1 && pop(c) == 2 && pop(c) == 3;
}

bool test_five_disks(bool iterative) {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(5);
    a.push(4);
    a.push(3);
    a.push(2);
    a.push(1);

    if (iterative) move_it(a, b, c, 5);
    else move(a, b, c, 5);
    return a.empty() && b.empty() && c.size() == 5 &&
           pop(c) == 1 && pop(c) == 2 && pop(c) == 3 &&
           pop(c) == 4 && pop(c) == 5;
}

int main() {
    int counter = 0;
    if (!test_one_disk(false)) {
        cout << "One disk test failed!" << endl;
        counter++;
    }
    if (!test_one_disk(true)) {
        cout << "One disk iterative test failed!" << endl;
        counter++;
    }
    if (!test_two_disks(false)) {
        cout << "Two discs test failed!" << endl;
        counter++;
    }
    if (!test_two_disks(true)) {
        cout << "Two discs iterative test failed!" << endl;
        counter++;
    }
    if (!test_three_disks(false)) {
        cout << "Three discs test failed!" << endl;
        counter++;
    }
    if (!test_three_disks(true)) {
        cout << "Three discs iterative test failed!" << endl;
        counter++;
    }
    if (!test_five_disks(false)) {
        cout << "Five discs test failed!" << endl;
        counter++;
    }
    if (!test_five_disks(true)) {
        cout << "Five discs iterative test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

