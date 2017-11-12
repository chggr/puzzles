#include <stdlib.h>
#include <stdio.h>

// Task description: Write your own implementation of malloc so that it
// supports allocating memory such that the memory address is divisible by a
// specific power of two. Additionally write the corresponding free function.
//
// E.g. aligned_malloc(100, 16) : returns a memory address that is multiple of
//                                16 and points to memory of size 100 bytes.
//
//      aligned_free(ptr): frees memory allocated by aligned_malloc()
//
// Solution: The standard malloc() returns a pointer to a block of memory that
// could start at any address in the heap. In order to ensure that the address
// is aligned, we will need to request more memory and return an address within
// that space that satisfies the requirement.
//
// The amount of extra memory required would be equal to the given alignment
// number minus one. This will ensure that in the space returned by malloc there
// is at least one address that satisfies the criteria. To find this address, we
// add the offset to the pointer returned by malloc and then clear out the last
// few bits. This ensures that the returned address is both divisible by the
// alignment number and also within the space that malloc has returned.
//
// In order to free the space allocated with alligned_malloc(), we will need to
// know the address that was originally returned by malloc(), This information
// is saved in the bytes just before the address returned by alligned_malloc().

void* aligned_malloc(size_t size, size_t align) {
    size_t offset = align - 1 + sizeof(void*);

    void* orig = (void*) malloc(size + offset);
    if (orig == NULL) return NULL;

    void* final = (void*) (((size_t)(orig) + offset) & ~(align - 1));
    ((void**) final)[-1] = orig;
    return final;
}

void aligned_free(void* ptr) {
    void* orig = ((void**) ptr)[-1];
    free(orig);
}

int test_aligned_malloc() {
    void* ptr2 = aligned_malloc(100, 2);
    void* ptr8 = aligned_malloc(100, 8);
    void* ptr16 = aligned_malloc(100, 16);
    void* ptr128 = aligned_malloc(100, 128);
    void* ptr1024 = aligned_malloc(100, 1024);

    int ret = 0 == (((size_t) ptr2) % 2) &&
              0 == (((size_t) ptr8) % 8) &&
              0 == (((size_t) ptr16) % 16) &&
              0 == (((size_t) ptr128) % 128) &&
              0 == (((size_t) ptr1024) % 1024);

    aligned_free(ptr2);
    aligned_free(ptr8);
    aligned_free(ptr16);
    aligned_free(ptr128);
    aligned_free(ptr1024);

    return ret;
}

int main() {
    int counter = 0;
    if (!test_aligned_malloc()) {
        printf("Align malloc test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

