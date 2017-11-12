#include <iostream>

// Task description: Write a smart pointer class in C++. A smart pointer
// simulates a real pointer but also provides automatic garbage collection. It
// automatically counts the number of references to the target object and
// releases the memory when the count reaches zero.
//
// Solution: The SmartPointer templated class defined below contains two
// pointers, one to the referenced object and another to an unsigned integer
// containing the total count of references. The count of references also
// needs to be a pointer, since it will be tracked across multiple
// SmartPointers to the same object. As each SmartPointer is destructed, the
// count of references is decreased until it reaches zero, at which point the
// memory allocated to the referenced object is freed.
//
// The equals operator has also been defined for SmartPointer so that it
// decrements the count of references to the object it is currently pointing at
// before it gets repointed to the new address.

template <class T> class SmartPointer {

    private:
        T* ref;
        unsigned* ref_count;

        void clean() {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ref;
                delete ref_count;
                ref = NULL;
                ref_count = NULL;
            }
        }

    public:
        SmartPointer(T* ptr) {
            ref = ptr;
            ref_count = new unsigned;
            *ref_count = 1;
        }

        SmartPointer(SmartPointer<T>& sptr) {
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            (*ref_count)++;
        }

        ~SmartPointer() {
            clean();
        }

        SmartPointer<T>& operator=(SmartPointer<T>& sptr) {
            if (this == &sptr) return *this;
            if (*ref_count > 0) clean();

            ref = sptr.ref;
            ref_count = sptr.ref_count;
            (*ref_count)++;
            return *this;
        }

        T getValue() {
            return *ref;
        }

        unsigned getRefCount() {
            return *ref_count;
        }
};

bool test_constructors() {
    int* ptr = new int;
    *ptr = 10;

    SmartPointer<int> sptr(ptr);
    SmartPointer<int> sptr2(sptr);

    return 10 == sptr.getValue() &&
           10 == sptr2.getValue() &&
           2 == sptr.getRefCount() &&
           2 == sptr2.getRefCount();
}

bool test_operator_equals() {
    int* ptr = new int;
    int* ptr2 = new int;

    SmartPointer<int> sptr(ptr);
    SmartPointer<int> sptr2(ptr2);
    SmartPointer<int> sptr3(sptr2);
    sptr2 = sptr;

    return 2 == sptr.getRefCount() &&
           2 == sptr2.getRefCount() &&
           1 == sptr3.getRefCount();
}

int main() {
    int counter = 0;
    if (!test_constructors()) {
        std::cout << "Constructors test failed!" << std::endl;
        counter++;
    }
    if (!test_operator_equals()) {
        std::cout << "Operator equals test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

