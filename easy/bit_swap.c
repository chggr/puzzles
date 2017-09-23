#include <stdio.h>

// Task description: Given an integer, write a method to swap odd and even bits.
//
// E.g. For integer 0b11010111 the answer is 0b11101011.
//
// Solution: The implementation below first retrieves the even bits using hex
// number 0xaaaaaaaa (a = 1010) and moves them by one position to the right.
// It subsequently retrieves the odd bits using hex number 0x55555555
// (5 = 0101) and moves them by one position to the left. The end result is
// obtained using an OR operation on these two numbers.

int bit_swap(int number) {
    return ((number & 0xaaaaaaaa) >> 1) |
           ((number & 0x55555555) << 1);
}

int test_bit_swap() {
    return 0b1111 == bit_swap(0b1111) &&
           0b1010 == bit_swap(0b0101) &&
           0b1110 == bit_swap(0b1101) &&
           0 == bit_swap(0) & 
           ~0 == bit_swap(~0);
}

int main() {
    int counter = 0;
    if(!test_bit_swap()) {
        printf("Bit swap test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

