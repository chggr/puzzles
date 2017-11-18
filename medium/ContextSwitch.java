import java.util.concurrent.CountDownLatch;

// Task description: How would you measure the time spent in a context switch?
//
// Solution: A context switch is the time spent switching between two processes
// or threads. Measuring it is very tricky because it can be quite variable and
// depends on multiple factors, such as hardware interrupts that have happened
// in the meanwhile, the scheduling algorithm, etc.
//
// The implementation below is an initial attempt at measuring the time spent
// in a context switch. Two threads are created and the time taken to transfer
// execution from one thread to the other is measured and reported. The program
// will need to be executed multiple times in order to obtain an average value
// that would be close to the actual time required for a context switch. This
// currently takes on average around 32 microseconds in my system.

public class ContextSwitch {

    private final CountDownLatch begin = new CountDownLatch(1);
    private final CountDownLatch latch = new CountDownLatch(1);

    private long start;
    private long finish;

    private final Thread threadA = new Thread(() -> {
        try {
            begin.await();
            start = System.nanoTime();
            latch.countDown();
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
    });

    private final Thread threadB = new Thread(() -> {
        try {
            begin.await();
            latch.await();
            finish = System.nanoTime();
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
    });

    private void time() throws InterruptedException {
        threadA.start();
        threadB.start();

        Thread.sleep(10);
        begin.countDown();

        threadA.join();
        threadB.join();
        System.out.println("Context switch time: " + (finish - start) + " ns");
    }

    public static void main(String[] args) throws InterruptedException {
        new ContextSwitch().time();
    }
}

