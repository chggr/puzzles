import java.util.Random;

// Task description: Implement a BlockingQueue of a fixed size that will allow
// a producer thread to enqueue objects and a consumer thread to dequeue them.
// Ensure that there is proper synchronization to avoid race conditions and
// deadlocks.
//
// Solution: The implementation below uses an array as the underlying data
// structure. In order to implement a thread safe solution, we need to control
// access to the shared resource. Thus we define all public methods as
// synchronized, so that only one thread can access and modify the array at any
// given time.
//
// The BlockingQueue should block if a thread tries to take an item and it is
// empty or if a thread tries to put an item and it is full. To achieve that we
// use the wait() / notify() mechanism. A thread that tries to take from an
// empty queue will wait() until it is notified by another thread that an item
// has been added. A similar approach is also followed when a thread tries to
// put an item to a full queue. Note that we need to notify only when we take
// from a full queue or put to an empty queue. In all other instances, no thread
// will be waiting.

public class BlockingQueue<T> {

    private final T[] array;
    private int takeIndex;
    private int putIndex;

    public BlockingQueue(int size) {
        array = (T[]) new Object[size];
        takeIndex = 0;
        putIndex = 0;
    }

    public synchronized T take() {
        while (isEmpty()) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }

        if (isFull()) {
            notify();
        }

        T item = array[takeIndex % array.length];
        takeIndex++;
        reduceIndices();
        return item;
    }

    public synchronized void put(T item) {
        while (isFull()) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }

        if (isEmpty()) {
            notify();
        }

        array[putIndex % array.length] = item;
        putIndex++;
        reduceIndices();
    }

    public synchronized boolean isEmpty() {
        return takeIndex == putIndex;
    }

    public synchronized boolean isFull() {
        return putIndex - takeIndex >= array.length;
    }

    private void reduceIndices() {
        if (takeIndex > array.length && putIndex > array.length) {
            takeIndex -= array.length;
            putIndex -= array.length;
        }
    }

    public static void main(String[] args) {
        final Random random = new Random(System.currentTimeMillis());
        final BlockingQueue<Integer> queue = new BlockingQueue<>(10);

        final Thread producer = new Thread(() -> {
            while (true) {
                int num = random.nextInt(1000);
                try {
                    Thread.sleep(num);
                } catch (InterruptedException e) { }
                queue.put(num);
                System.out.println("Producer put " + num);
            }
        });

        final Thread consumer = new Thread(() -> {
            while (true) {
                try {
                    Thread.sleep(random.nextInt(1000));
                } catch (InterruptedException e) { }
                int num = queue.take();
                System.out.println("Consumer took " + num);
            }
        });

        producer.start();
        consumer.start();

        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) { }
    }
}

