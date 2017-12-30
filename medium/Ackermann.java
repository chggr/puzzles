import java.util.HashMap;
import java.util.Map;

// Task description: Write a method to implement the Ackermann function defined
// below for non-negative integers m and n. Can this function be written
// iteratively instead of recursively? What can be done to speed up the
// implementation?
//
//             n + 1                  if m = 0
// A(m, n) =   A(m - 1, 1)            if m > 0 and n = 0
//             A(m - 1, A(m, n - 1)   if m > 0 and n > 0
//
// Solution: The Ackermann function is one of the earliest and simplest examples
// of a total computable function that is not primitive recursive. This means
// that this function cannot be written iteratively but guarantees to arrive to
// a result for all possible input values. The result grows quite rapidly, even
// for relatively small inputs.
//
// The first implementation below is a basic recursive method. It takes quite a
// bit of time to compute the result, even for relatively small input values.
// The second implementation is also recursive but uses memoization to save and
// reuse results of intermediate computations, thus speeding up total execution
// time. Computing A(4,1) using the first method takes around 23 seconds on my
// machine, whereas only around 270 ms with the second approach. Please note the
// maximum stack size will need to be increased (-Xss parameter) to be able to
// run for high input values.

public class Ackermann {

    // Basic recursive Ackermann implementation.
    private static final int A(int m, int n) {
        if (m < 0 || n < 0) return -1;

        if (m == 0) return n + 1;
        if (n == 0) return A(m - 1, 1);
        return A(m - 1, A(m, n - 1));
    }

    private static final class Input {

        private final int m;
        private final int n;

        public Input(int m, int n) {
            this.m = m;
            this.n = n;
        }

        @Override
        public boolean equals(Object o) {
            if (!(o instanceof Input)) return false;
            if (o == this) return true;

            final Input other = (Input) o;
            return this.m == other.m && this.n == other.n;
        }

        @Override
        public int hashCode() {
            int result = 17;
            result = 31 * result + m;
            result = 31 * result + n;
            return result;
        }
    }

    private static final Map<Input, Integer> memo = new HashMap<>();

    // Recursive Ackermann implementation using memoization.
    private static final int Amemo(int m, int n) {
        if (m < 0 || n < 0) return -1;

        final Input input = new Input(m, n);
        if (memo.containsKey(input)) {
            return memo.get(input);
        }

        int value;
        if (m == 0) {
            value = n + 1;
        } else {
            if (n == 0) value = Amemo(m - 1, 1);
            else value = Amemo(m - 1, Amemo(m, n - 1));
        }

        memo.put(input, value);
        return value;
    }

    private static boolean testNegativeInput() {
        return -1 == A(-1, 0) && -1 == Amemo(-1, 0) &&
               -1 == A(0, -1) && -1 == Amemo(0, -1);
    }

    private static boolean testZeroInput() {
        return 1 == A(0, 0) && 1 == Amemo(0, 0) &&
               2 == A(0, 1) && 2 == Amemo(0, 1) &&
               2 == A(1, 0) && 2 == Amemo(1, 0);
    }

    private static boolean testPositiveInput() {
        return 4 == A(0, 3) && 4 == Amemo(0, 3) &&
               4 == A(1, 2) && 4 == Amemo(1, 2) &&
               5 == A(1, 3) && 5 == Amemo(1, 3) &&
               13 == A(3, 1) && 13 == Amemo(3, 1) &&
               61 == A(3, 3) && 61 == Amemo(3, 3) &&
               65533 == A(4, 1) && 65533 == Amemo(4, 1);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNegativeInput()) {
            System.out.println("Negative input test failed!");
            counter++;
        }
        if (!testZeroInput()) {
            System.out.println("Zero input test failed!");
            counter++;
        }
        if (!testPositiveInput()) {
            System.out.println("Positive input test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

