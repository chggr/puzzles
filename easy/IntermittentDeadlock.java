import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

// Task description: Think of and implement a scenario where two threads are
// involved into a deadlock intermittently. Some executions of the program
// should result in a deadlock, while other executions should not.
//
// Solution: In the implementation below we have two threads that are competing
// for the same resources. The first is trying to acquire lockA and then lockB,
// whereas the second attempts to acquire lockB and then lockA. Both are
// started simultaneously and a race condition develops. In many executions
// either threadA or threadB manages to successfully get both locks, thus
// executing first. But there are some cases where they are deadlocked: threadA
// holds lockA and is waiting for lockB, whereas threadB holds lockB and is
// waiting for lockA. This deadlock scenario can be avoided if both threads
// attempt to acquire the locks in the same order.

public class IntermittentDeadlock {

    private final Lock lockA = new ReentrantLock();
    private final Lock lockB = new ReentrantLock();

    private final Thread threadA = new Thread(() -> {
        System.out.println("Thread A: started");
        lockA.lock();
        System.out.println("Thread A: got lock A");
        lockB.lock();
        System.out.println("Thread A: got lock B");
        lockB.unlock();
        System.out.println("Thread A: released lock B");
        lockA.unlock();
        System.out.println("Thread A: released lock A");
        System.out.println("Thread A: finished");
    });

    private final Thread threadB = new Thread(() -> {
        System.out.println("Thread B: started");
        lockB.lock();
        System.out.println("Thread B: got lock B");
        lockA.lock();
        System.out.println("Thread B: got lock A");
        lockA.unlock();
        System.out.println("Thread B: released lock A");
        lockB.unlock();
        System.out.println("Thread B: released lock B");
        System.out.println("Thread B: finished");
    });

    public void deadlock() throws InterruptedException {
        threadA.start();
        threadB.start();
        threadA.join();
        threadB.join();
    }

    public static void main(String[] args) throws InterruptedException {
        new IntermittentDeadlock().deadlock();
    }
}

