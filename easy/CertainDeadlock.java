import java.util.concurrent.CountDownLatch;

// Task description: Think of and implement a scenario where two threads are
// involved into a deadlock. All executions of the program should result in
// a deadlock between these two threads.
//
// Solution: In the implementation below we have two threads that are waiting
// on each other and are therefore involved into a certain deadlock. The first
// thread is waiting for latchB to be released before proceeding to release
// latchA. On the contrary the second thread is waiting for latchA to be
// released before proceeding to release latchB. Both threads are started
// simultaneously and end up in a certain deadlock because threadA is waiting
// for threadB to release latchB and threadB is waiting for threadA to release
// latchA.

public class CertainDeadlock {

    private final CountDownLatch latchA = new CountDownLatch(1);
    private final CountDownLatch latchB = new CountDownLatch(1);

    private final Thread threadA = new Thread(() -> {
        System.out.println("Thread A: started");
        try {
            System.out.println("Thread A: waiting for latchB");
            latchB.await();
            System.out.println("Thread A: latchA countDown");
            latchA.countDown();
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
        System.out.println("Thread A: finished");
    });

    private final Thread threadB = new Thread(() -> {
        System.out.println("Thread B: started");
        try {
            System.out.println("Thread B: waiting for latchA");
            latchA.await();
            System.out.println("Thread B: latchB countDown");
            latchB.countDown();
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
        System.out.println("Thread B: finished");
    });

    public void deadlock() throws InterruptedException {
        threadA.start();
        threadB.start();
        threadA.join();
        threadB.join();
    }

    public static void main(String[] args) throws InterruptedException {
        new CertainDeadlock().deadlock();
    }
}

