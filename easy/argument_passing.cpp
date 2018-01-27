#include <iostream>
#include <vector>

// Task description: Enumerate the different ways of passing arguments to
// methods in C++ and explain how each one works.
//
// Solution: There are a lot of ways of passing arguments in methods in C++,
// some of which are listed below.
//
// - Pass by value
//   When passing by value the object's copy constructor will be called to
//   duplicate the object on the stack. If the object does not have a copy
//   constructor, the compiler will generate a default one that will simply
//   copy all its fields. This might lead to unexpected bugs if the object
//   contains pointers to resources that it owns (e.g. pointers to dynamically
//   allocated memory or file handles). The method will not operate on the
//   original object, but to the duplicated object. Therefore any changes made
//   to it will not be reflected in the original object. This is the least
//   efficient way to pass arguments, because the object is copied every time
//   the method is called.
//
// - Pass by pointer
//   In this case the object is passed by a pointer and thus only the address
//   of the object is copied on the stack. Any changes the method makes will
//   be reflected to the original object.
//
// - Pass by reference
//   This case is similar to passing by pointer. It involves no copying of the
//   object into the stack and allows the method to operate directly on the
//   original object. The obvious difference is that we need to use the arrow
//   notation (->) to call a method on a pointer, whereas we can use the dot (.)
//   notation to call the method on a reference. More importantly, a reference
//   is guaranteed to refer to an object, whereas a pointer may actually be
//   NULL.
//
// - Pass by constant pointer
//   This is similar to passing by pointer but the method is prevented from
//   modifying the object and it can only call object member functions that have
//   been defined as const.
//
// - Pass by reference to pointer
//   In this case the argument passed into the method is a reference to a
//   pointer and any changes made to that object in the calling function are
//   seen by the caller. Since the argument is a reference to a pointer, if
//   it is modified to point to a different object, the pointer in the calling
//   function will be modified as well.

using namespace std;

void pass_by_value(vector<int> v, int i) {
    v.push_back(i);
}

void pass_by_pointer(vector<int> *v, int i) {
    v->push_back(i);
}

void pass_by_reference(vector<int> &v, int i) {
    v.push_back(i);
}

void pass_by_const_pointer(const vector<int> *v, int i) {
    v->size();
}

void pass_by_pointer_reference(vector<int> *&v, int i) {
    vector<int> newVector;
    v = &newVector;
    v->push_back(i);
}

bool test_pass_by_value() {
    vector<int> v;
    pass_by_value(v, 10);
    return v.empty();
}

bool test_pass_by_pointer() {
    vector<int> v;
    pass_by_pointer(&v, 10);
    return !v.empty();
}

bool test_pass_by_reference() {
    vector<int> v;
    pass_by_reference(v, 10);
    return !v.empty();
}

bool test_pass_by_const_pointer() {
    vector<int> v;
    pass_by_const_pointer(&v, 10);
    return v.empty();
}

bool test_pass_by_pointer_reference() {
    vector<int> v;
    vector<int> *p = &v;
    pass_by_pointer_reference(p, 10);
    return v.empty() && !p->empty() && p != &v;
}

int main() {
    int counter = 0;
    if (!test_pass_by_value()) {
        cout << "Pass by value test failed!" << endl;
        counter++;
    }
    if (!test_pass_by_pointer()) {
        cout << "Pass by pointer test failed!" << endl;
        counter++;
    }
    if (!test_pass_by_reference()) {
        cout << "Pass by reference test failed!" << endl;
        counter++;
    }
    if (!test_pass_by_const_pointer()) {
        cout << "Pass by const pointer test failed!" << endl;
        counter++;
    }
    if (!test_pass_by_pointer_reference()) {
        cout << "Pass by pointer reference test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

