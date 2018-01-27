#include <stdio.h>

// Task description: Write a function to determine if this computer is little
// or big endian.
//
// Solution: Endianness refers to the order in which a computer stores the bytes
// of a multi-byte value. For example there are four bytes in a 32-bit integer
// and can be stored either from the least significant to the most significant or
// the other way around. In a big endian machine, the most significant byte is
// stored in the lowest address, whereas in a little endian machine the least
// significant byte is stored in the lowest address. The example below shows how
// an integer equal to one would be stored using the two formats.
//
//                   BYTE_1       BYTE_2       BYTE_3       BYTE_4
// Little-endian:   00000001     00000000     00000000     00000000
// Big-endian:      00000000     00000000     00000000     00000001
//
// The Java Virtual Machine is big-endian regardless of the underlying processor
// type. Therefore the function to determine endianness needs to be written in
// C. The first function below initially allocates an integer (four bytes) and
// sets its value to one. It then tests whether the first byte stored is zero or
// one to find out whether the computer is big or little endian. The second
// function works in a similar way but uses a union to store both an integer and
// a character in the same memory location. It then sets the integer to one and
// uses the character to read the first byte.

int little_endian() {
    int num = 1;
    char* c = (char *) &num;
    return *c;
}

int little_endian_union() {
    union {
        int i;
        char c;
    } temp;
    temp.i = 1;
    return temp.c;
}

int test_little_endian() {
    return little_endian() == little_endian_union();
}

int main() {
    if (!test_little_endian()) {
        printf("Little endian test failed!\n");
        return 1;
    }

    printf("This computer is ");
    if (little_endian()) {
        printf("little-endian.\n");
    } else {
        printf("big-endian.\n");
    }
}

