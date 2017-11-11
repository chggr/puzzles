#include <iostream>

// Task description: Given a stream of any type of elements, write a class that
// will be able to save and return the last K elements of the stream.
//
// E.g. for int stream {1, 2, 3, 4, 5, 6, 7, 8, 9} and K = 3
//      the answer is {7, 8, 9}
//
// Solution: The implementation below uses a circular array of length K to
// store the latest K elements of the stream. Upon receipt of a new element
// the oldest element of the array is substituted with that new element.

template <class T> class StreamStore {

    private:
        T* array;
        int maxSize;
        int counter;

    public:
        StreamStore(int maxSize) : maxSize(maxSize), counter(0) {
            array = new T[maxSize];
        }

        ~StreamStore() {
            delete array;
        }

        void put(T element);
        int size();
        T* get();
};

template <class T> void StreamStore<T>::put(T element) {
    array[counter % maxSize] = element;
    counter++;
}

template <class T> int StreamStore<T>::size() {
    return counter < maxSize ? counter : maxSize;
}

template <class T> T* StreamStore<T>::get() {
    if (counter == 0) {
        return NULL;
    }

    T* output;
    if (counter < maxSize) {
        output = new T[counter];
        for (int i = 0; i < counter; i++) {
            output[i] = array[i];
        }
    } else {
        output = new T[maxSize];
        int pos = counter % maxSize;
        for (int i = 0; i < maxSize; i++) {
            output[i] = array[(pos + i) % maxSize];
        }
    }
    return output;
}

bool test_empty_stream() {
    StreamStore<int> store(5);
    return NULL == store.get();
}

bool test_small_stream() {
    StreamStore<int> store(5);
    store.put(1);
    store.put(2);
    store.put(3);

    int* output = store.get();
    bool result = 3 == store.size() &&
                  1 == output[0] &&
                  2 == output[1] &&
                  3 == output[2];
    delete output;
    return result;
}

bool test_large_stream() {
    StreamStore<int> store(5);
    for (int i = 1; i < 100; i++) {
        store.put(i);
    }

    int* output = store.get();
    bool result =  5 == store.size() &&
                   95 == output[0] &&
                   96 == output[1] &&
                   97 == output[2] &&
                   98 == output[3] &&
                   99 == output[4];
    delete output;
    return result;
}

int main() {
    int counter = 0;
    if (!test_empty_stream()) {
        std::cout << "Empty stream test failed!" << std::endl;
        counter++;
    }
    if (!test_small_stream()) {
        std::cout << "Small stream test failed!" << std::endl;
        counter++;
    }
    if (!test_large_stream()) {
        std::cout << "Large stream test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

