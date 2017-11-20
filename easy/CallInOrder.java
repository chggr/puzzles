import java.util.concurrent.CountDownLatch;

// Task description: Suppose we have a class named InOrder that defines three
// methods as shown below. The same instance of InOrder will be passed to three
// separate threads. ThreadA will call first(), ThreadB will call second() and
// ThreadC will call third(). Design a mechanism to ensure that these methods
// will always be called in order, i.e. first() will called before second() and
// second will be called before third.
//
// public class InOrder {
//     public void first() { }
//     public void second() { }
//     public void third() { }
// }
//
// Solution: Using ReentrantLocks here to guard when each method is executed is
// not possible because that would violate the concept of lock ownership. We
// would have to use two locks, lock them at InOrder object instantiation and
// unlock them as each method is executed. This would require the locks to be
// locked by one thread but unlocked by another thread, thus violating lock
// ownership principles and throwing an exception.
//
// The implementation below is instead using CountDownLatches to guard execution
// of each method. Once first() is called, the first latch is enabled thus
// unblocking any calls to second() and so on. Semaphores could also be used
// instead of CountDownLatches.

public class CallInOrder {

    public static class InOrder {

        private final CountDownLatch latch1 = new CountDownLatch(1);
        private final CountDownLatch latch2 = new CountDownLatch(1);

        public void first() {
            System.out.println("First method called.");
            latch1.countDown();
        }

        public void second() {
            try {
                latch1.await();
            } catch (InterruptedException e) {
                throw new IllegalStateException(e);
            }
            System.out.println("Second method called.");
            latch2.countDown();
        }

        public void third() {
            try {
                latch2.await();
            } catch (InterruptedException e) {
                throw new IllegalStateException(e);
            }
            System.out.println("Third method called.");
        }
    }

    public static void main(String[] args) throws InterruptedException {
        final InOrder inOrder = new InOrder();
        final Thread threadA = new Thread(() -> inOrder.first());
        final Thread threadB = new Thread(() -> inOrder.second());
        final Thread threadC = new Thread(() -> inOrder.third());

        threadC.start();
        threadB.start();
        threadA.start();

        threadC.join();
        threadB.join();
        threadA.join();
    }
}

