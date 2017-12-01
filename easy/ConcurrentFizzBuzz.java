import java.util.function.Function;
import java.util.function.Predicate;

// Task description: The game of FizzBuzz involves printing out all numbers
// from 1 to n, but print "Fizz" if the number is divisible by 3, "Buzz" if the
// number is divisible by 5 and "FizzBuzz" if the number is divisible by both 3
// and 5. Implement a multithreaded version of FizzBuzz that will consist of
// four threads: one to check and print "Fizz", one to check and print "Buzz",
// one to check and print "FizzBuzz" and one to check and print the number.
//
// Solution: In the implementation below we have defined a FizzBuzzThread class
// that extends Thread. Its constructor requires three parameters: A Predicate
// that will be used to check when to print something, a Function that defines
// what to print and finally the maximum number to evaluate. A private static
// field is used to hold the current value, which is in turn examined by each
// Thread and incremented only by the one whose Predicate returns true.
//
// Please note that the field holding the current value needs to be declared as
// volatile, because its value should never be cached thread-locally and the
// field itself will be modified by many threads. In this case we can avoid
// synchronizing against that field because the Predicates are mutually
// exclusive and it is guaranteed that only one thread will attempt to increase
// the value each time.

public class ConcurrentFizzBuzz {

    private static final class FizzBuzzThread extends Thread {

        private static volatile int value = 1;

        private final Predicate<Integer> predicate;
        private final Function<Integer, String> message;
        private final int max;

        public FizzBuzzThread(final Predicate<Integer> predicate,
                              final Function<Integer, String> message,
                              final int max) {

            this.predicate = predicate;
            this.message = message;
            this.max = max;
        }

        public void run() {
            while (true) {
                if (value > max) {
                    break;
                }

                if (predicate.test(value)) {
                    System.out.println(message.apply(value));
                    value++;
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        final Thread[] threads = {
            new FizzBuzzThread(i -> i % 3 == 0 && i % 5 == 0, i-> "FizzBuzz", 100),
            new FizzBuzzThread(i -> i % 3 == 0 && i % 5 != 0, i -> "Fizz", 100),
            new FizzBuzzThread(i -> i % 3 != 0 && i % 5 == 0, i -> "Buzz", 100),
            new FizzBuzzThread(i -> i % 3 != 0 && i % 5 != 0, String::valueOf, 100)
        };

        for (Thread t : threads) {
            t.start();
        }
    }
}

