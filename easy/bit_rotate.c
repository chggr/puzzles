#include <stdio.h>

// Task description: Given an integer write a method to rotate its bits by a
// given number. A rotation or circular shift is similar to normal bit shift
// except that any bits discarded at one end are added to the other end.
//
// E.g. Right shift integer 0xFFFF0000 by 2 will result in 0x00FFFF00
//
// Solution: The two methods implemented below can be used to perform right or
// left bit-wise rotation of an integer by the given number of bits. The input
// number in both methods is defined as unsigned int so that right rotation does
// not carry the sign bit for negative numbers.

int rotate_right(unsigned int num, unsigned int count) {
    count = count % 32;
    return (num >> count) | (num << (32 - count));
}

int rotate_left(unsigned int num, unsigned int count) {
    count = count % 32;
    return (num << count) | (num >> (32 - count));
}

int test_rotate_right_positive() {
    int num = 0x0000FFFF;
    return 0x0000FFFF == rotate_right(num, 0) &&
           0xF0000FFF == rotate_right(num, 4) &&
           0xFF0000FF == rotate_right(num, 8) &&
           0xFFF0000F == rotate_right(num, 12) &&
           0xFFFF0000 == rotate_right(num, 16) &&
           0x0000FFFF == rotate_right(num, 32) &&
           0xF0000FFF == rotate_right(num, 36) &&
           0xFF0000FF == rotate_right(num, 40) &&
           0xFFF0000F == rotate_right(num, 44) &&
           0xFFFF0000 == rotate_right(num, 48);
}

int test_rotate_right_negative() {
    int num = 0xFF0000FF;
    return 0xFF0000FF == rotate_right(num, 0) &&
           0xFFF0000F == rotate_right(num, 4) &&
           0xFFFF0000 == rotate_right(num, 8) &&
           0x0FFFF000 == rotate_right(num, 12) &&
           0x00FFFF00 == rotate_right(num, 16) &&
           0xFF0000FF == rotate_right(num, 32) &&
           0xFFF0000F == rotate_right(num, 36) &&
           0xFFFF0000 == rotate_right(num, 40) &&
           0x0FFFF000 == rotate_right(num, 44) &&
           0x00FFFF00 == rotate_right(num, 48);
}

int test_rotate_left_positive() {
    int num = 0x00FFFF00;
    return 0x00FFFF00 == rotate_left(num, 0) &&
           0x0FFFF000 == rotate_left(num, 4) &&
           0xFFFF0000 == rotate_left(num, 8) &&
           0xFFF0000F == rotate_left(num, 12) &&
           0xFF0000FF == rotate_left(num, 16) &&
           0x00FFFF00 == rotate_left(num, 32) &&
           0x0FFFF000 == rotate_left(num, 36) &&
           0xFFFF0000 == rotate_left(num, 40) &&
           0xFFF0000F == rotate_left(num, 44) &&
           0xFF0000FF == rotate_left(num, 48);
}

int test_rotate_left_negative() {
    int num = 0xFFFF0000;
    return 0xFFFF0000 == rotate_left(num, 0) &&
           0xFFF0000F == rotate_left(num, 4) &&
           0xFF0000FF == rotate_left(num, 8) &&
           0xF0000FFF == rotate_left(num, 12) &&
           0x0000FFFF == rotate_left(num, 16) &&
           0xFFFF0000 == rotate_left(num, 32) &&
           0xFFF0000F == rotate_left(num, 36) &&
           0xFF0000FF == rotate_left(num, 40) &&
           0xF0000FFF == rotate_left(num, 44) &&
           0x0000FFFF == rotate_left(num, 48);
}

int  main() {
    int counter = 0;
    if (!test_rotate_right_positive()) {
        counter++;
        printf("Rotate right positive number test failed!\n");
    }
    if (!test_rotate_right_negative()) {
        counter++;
        printf("Rotate right negative number test failed!\n");
    }
    if (!test_rotate_left_positive()) {
        counter++;
        printf("Rotate left positive test failed!\n");
    }
    if (!test_rotate_left_negative()) {
        counter++;
        printf("Rotate left negative test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

