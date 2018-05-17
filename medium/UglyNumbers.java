import java.util.PriorityQueue;

// Task description: Ugly numbers are numbers whose only prime factors are 2, 3
// and 5. Write a method to return the Nth ugly number in the sequence.
//
// E.g. for N = 10 the method should return 12
//      the first ugly numbers are {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15}
//
// Solution: The first implementation below is a brute force approach where we
// check every number from zero and above whether it is ugly and return the Nth
// ugly number found. The space complexity of this approach is O(1) but its
// efficiency deteriorates significantly as N increases.
//
// The second implementation is using a min heap to store ugly numbers. In each
// iteration we poll the root element of the heap and check whether this is the
// Nth ugly number. If not we add its multiples with 2, 3 and 5 to the heap.
// This algorithm performs faster than the previous approach, at the expense of
// space required for the min heap.

public class UglyNumbers {

    public static boolean isUgly(int num) {
        if (num <= 0) return false;
        while (num % 5 == 0) num /= 5;
        while (num % 3 == 0) num /= 3;
        while (num % 2 == 0) num /= 2;
        return num == 1;
    }

    public static int getUglyBrute(int num) {
        int result = 0;
        while (num > 0) {
            result++;
            if (isUgly(result)) num--;
        }
        return result;
    }

    public static int getUgly(int num) {
        PriorityQueue<Integer> queue = new PriorityQueue<>();
        queue.add(1);

        int result = 0;
        for (int i = 0; i < num; i++) {
            while (queue.peek() <= result) queue.poll();
            result = queue.poll();
            queue.add(result * 2);
            queue.add(result * 3);
            queue.add(result * 5);
        }
        return result;
    }

    public static boolean testIsUgly() {
        return isUgly(1) && isUgly(2) && isUgly(3) &&
               isUgly(5) && isUgly(12) && !isUgly(7) &&
               !isUgly(14) && !isUgly(0) && !isUgly(-1);
    }

    public static boolean testGetUglyBrute() {
        int[] expected = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15};
        for (int i = 0; i < expected.length; i++) {
            if (expected[i] != getUglyBrute(i)) return false;
        }
        return true;
    }

    public static boolean testGetUgly() {
        int[] expected = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15};
        for (int i = 0; i < expected.length; i++) {
            if (expected[i] != getUgly(i)) return false;
        }
        return true;
    }

    public static boolean testBoth() {
        for (int i = 0; i < 100; i++) {
            if (getUgly(i) != getUglyBrute(i)) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testIsUgly()) {
            counter++;
            System.out.println("Is ugly test failed!");
        }
        if (!testGetUglyBrute()) {
            counter++;
            System.out.println("Get ugly brute test failed!");
        }
        if (!testGetUgly()) {
            counter++;
            System.out.println("Get ugly test failed!");
        }
        if (!testBoth()) {
            counter++;
            System.out.println("Both get ugly test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

