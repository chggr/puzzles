#include <stdio.h>

// Task description: Write a program to find out whether the machine's stack
// grows downwards or upwards in memory.
//
// Solution: The stack is a region in memory where data is added and removed in
// a LIFO (last in first out) manner. Each thread has its own stack where a new
// frame is created when a method is invoked. The following information is
// stored in that frame: return address, saved registers, local variables and
// input parameters. When a method returns, its full frame is popped from the
// stack and therefore all memory allocated on the stack for local variables is
// automatically and efficiently reclaimed. Therefore stack based allocation is
// suitable for temporary data or data that is no longer required after the
// function exits. Allocating more memory on the stack than is available can
// result in a crash due to stack overflow.
//
// On the other hand, the heap is a region in memory that is not automatically
// managed and can be used to allocate memory for data that will be used across
// method calls. Allocating memory on the heap can be done through malloc() and
// the developer is responsible for freeing up any allocated memory when it is
// no longer required. Failure to do so will result in a memory leak, i.e. an
// unused portion of memory that is still allocated. Unlike the stack, heap does
// not have any size restrictions on variable size, except from physical size of
// available memory. Allocating memory on the heap is slightly slower to be read
// and written to compared to the stack.
//
// The program below checks whether the current machine's stack grows downwards
// or upwards in memory. This is dependent on the underlying computer
// architecture (e.g. for x86 stack grows downwards). A caller method allocates
// a temporary variable in the stack and passes the pointer to the callee method.
// This in turn creates another temporary variable in the stack and compares the
// two pointers to identify whether the stack has grown backwards or forwards.

void callee(int* p) {
    int temp;
    int diff = (p - &temp);
    printf("The stack in this machine grows %s\n",
            diff > 0 ? "downwards" : "upwards");
}

int caller() {
    int temp;
    callee(&temp);
}

int main() {
    caller();
}

