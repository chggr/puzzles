#include <iostream>

// Task description: What are the differences between macros and inline methods
// in C / C++? When would you use each?
//
// Solution: In the example below we have implemented a simple method to return
// the maximum of two values both as a macro and as an inline method. Both
// macros and inline methods provide a way to eliminate function call overhead
// at the expense of program size. The differences, pros and cons of each
// approach are examined below:
//
// Macros are implemented with simple text replacement. The preprocessor will
// scan the file and replace any references to the macro with its definition
// before the code is compiled. Macros are typically used in cases where an
// expression is complex and is used often enough to warrant abstraction behind
// a pretty name, but is too simple to be worth the overhead of a function call.
// Unfortunately in many cases macros can lead to subtle bugs that are not
// obvious by looking at the source code. For example:
//
// #define SQUARE(x) x*x
//
// int val = 2;
// return SQUARE(++val);
//
// In this example the substitution will yield: return ++val * ++val and thus
// the returned value might be 12, different than the expected value of 9. This
// problem would not occur if SQUARE was implemented as an inline method.
//
// Inline methods are defined using the keyword inline and are handled directly
// by the compiler, therefore have better type safety than macros. The compiler
// will compile an inline function and will write a copy of the compiled code
// wherever the method is used, instead of generating a function call. Note that
// the inline keyword is just a hint and does not guarantee inlining. The
// compiler will ultimately decide whether to inline or not, based on its own
// calculations of what will yield the best performance.
//
// Overall inline functions should be preferred to macros where it makes sense
// because macros can be a source of subtle bugs and the compiled code is not
// visible in the source file. Macros were included in later versions of C++
// mainly for backwards compatibility reasons.

#define MAX(A, B) ((A) > (B) ? (A) : (B))

inline int max(int a, int b) {
    return a > b ? a : b;
}

bool test_max_macro() {
    return 10 == MAX(10, 10) &&
           10 == MAX(3, 10) &&
           10 == MAX(-14, 10);
}

bool test_max_inline() {
    return 10 == max(10, 10) &&
           10 == max(3, 10) &&
           10 == max(-14, 10);
}

int main() {
    int counter = 0;
    if (!test_max_macro()) {
        std::cout << "Max macro test failed!" << std::endl;
        counter++;
    }
    if (!test_max_inline()) {
        std::cout << "Max inline test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

