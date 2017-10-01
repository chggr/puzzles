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
//        A            B       C              A        B             C
//        |            |       |              |        |            [|]
//       [|]           |       |              |        |           [ | ]
//      [ | ]          |       |              |        |          [  |  ]
//     [  |  ]         |       |              |        |         [   |   ]
//    [   |   ]        |       |              |        |        [    |    ]
//   [    |    ]       |       |              |        |       [     |     ]
//
// Solution: The implementation below is a simple recursive solution to the
// Towers of Hanoi problem. The base case is for n = 1, where only one disk
// needs to move from tower A to tower C. Every other case (n > 1) can be
// deconstructed by first moving n - 1 disks from tower A to tower B, then
// moving disk n to tower C and finally moving the n - 1 disks from tower B
// to tower C.

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

bool test_one_disk() {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(1);

    move(a, b, c, 1);
    return a.empty() && b.empty() && c.size() == 1 && c.top() == 1;
}

bool test_two_disks() {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(2);
    a.push(1);

    move(a, b, c, 2);
    return a.empty() && b.empty() && c.size() == 2 &&
           pop(c) == 1 && pop(c) == 2;
}

bool test_three_disks() {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(3);
    a.push(2);
    a.push(1);

    move(a, b, c, 3);
    return a.empty() && b.empty() && c.size() == 3 &&
           pop(c) == 1 && pop(c) == 2 && pop(c) == 3;
}

bool test_five_disks() {
    stack<int> a;
    stack<int> b;
    stack<int> c;
    a.push(5);
    a.push(4);
    a.push(3);
    a.push(2);
    a.push(1);

    move(a, b, c, 5);
    return a.empty() && b.empty() && c.size() == 5 &&
           pop(c) == 1 && pop(c) == 2 && pop(c) == 3 &&
           pop(c) == 4 && pop(c) == 5;
}

int main() {
    int counter = 0;
    if (!test_one_disk()) {
        cout << "One disk test failed!" << endl;
        counter++;
    }
    if (!test_two_disks()) {
        cout << "Two discs test failed!" << endl;
        counter++;
    }
    if (!test_three_disks()) {
        cout << "Three discs test failed!" << endl;
        counter++;
    }
    if (!test_five_disks()) {
        cout << "Five discs test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

