import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.CountDownLatch;
import java.util.List;

// Task description: In the dining philosophers problem, a group of
// philosophers are sitting around a circular table with one chopstick between
// each of them. A philosopher needs both chopsticks to eat and always attempts
// to pick up the left one before the one on the right. Using threads and locks
// implement a simulation of the dining philosophers problem. Could a deadlock
// occur and what needs to be done to avoid it?
//
// Solution: A deadlock can occur if all philosophers reach out for the
// chopstick at their left and then all wait for the chopstick at their right.
// The implementation below simulates this problem. To avoid the deadlock we
// could follow one of two approaches:
//
// (1) Each philosopher could continuously attempt to acquire both chopsticks,
// first the left and then the right. If an attempt fails, any chopsticks taken
// should be put back on the table. This will allow other philosophers to use
// the chopsticks and will prevent a deadlock. In order to implement this
// approach we could use lock.tryLock() to attempt to acquire the lock but not
// block until it becomes available. This solution though will not work if the
// philosophers are perfectly synchronized, because all would continuously pick
// the left chopstick, then fail to pick the right chopstick, put down the left
// chopstick and repeat this process forever. In practice though, the threads
// are never perfectly synchronized and thus this solution is adequate.
//
// (2) Alternatively we could break the circle by having all philosophers first
// reach out for the left chopstick and then the right, except from one
// philosopher that will attempt to take the chopsticks in reverse order.

public class DiningPhilosophers {

    public static class Chopstick {

        private final ReentrantLock lock = new ReentrantLock();

        public void pickUp() {
            lock.lock();
        }

        public void putDown() {
            lock.unlock();
        }
    }

    public static class Philosopher extends Thread {

        private final int index;
        private final Chopstick left;
        private final Chopstick right;

        public Philosopher(int index, Chopstick left, Chopstick right) {
            this.index = index;
            this.left = left;
            this.right = right;
        }

        private void pickUp() {
            left.pickUp();
            right.pickUp();
        }

        private void putDown() {
            right.putDown();
            left.putDown();
        }

        private void eat() {
            System.out.println("Philosopher " + index + " eats.");
        }

        public void run() {
            pickUp();
            eat();
            putDown();
        }
    }

    public static class Dinner {

        private final List<Philosopher> philosophers;
        private final List<Chopstick> chopsticks;

        private Dinner(int guestCount) {

            chopsticks = new ArrayList<>();
            for (int i = 0; i < guestCount + 1; i++) {
                chopsticks.add(new Chopstick());
            }

            philosophers = new ArrayList<>();
            for (int i = 0; i < guestCount; i++) {
                Chopstick right = chopsticks.get(i);
                Chopstick left = chopsticks.get(i == 0 ? guestCount : i - 1);
                philosophers.add(new Philosopher(i, left, right));
            }
        }

        public void start() {
            philosophers.forEach(p -> p.start());
        }

        public void await() throws InterruptedException {
            for (Philosopher p : philosophers) {
                p.join();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 10; i++) {
            Dinner dinner = new Dinner(20);
            dinner.start();
            dinner.await();
        }
    }
}

