import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

// Task description: Given any positive integer, find the next higher integer
// that uses exactly the same digits. If the given number is negative or zero,
// return zero. In cases where no higher integer with the same digits exists,
// return the number provided.
//
// E.g. For input 1234 the answer is 1243
//      For input -10 the answer is 0
//      For input 0 the answer is 0
//      For input 98765 the answer is 98765
//
// Solution: The first implementation below uses a simple brute force approach
// to solve this task. It first extracts the digits of the given number and then
// iteratively examines all numbers higher than that to identify a match. The
// runtime complexity of this approach is O(n * 10^n), where n is the number of
// digits in the given integer. The algorithm potentially examines 10^n
// candidates and for each one extracts and compares its digits.

public class HigherWithSameDigits {

    private static int find(int number) {
        if (number <= 0) {
            return 0;
        }

        final List<Integer> digits = getDigits(number);
        for (int i = number + 1; ; i++) {
            final List<Integer> iDigits = getDigits(i);
            if (iDigits.size() != digits.size()) {
                break;
            }
            if (listEquals(digits, iDigits)) {
                return i;
            }
        }
        return number;
    }

    private static List<Integer> getDigits(int number) {
        final List<Integer> digits = new ArrayList<>();
        while(number >= 10) {
            digits.add(number % 10);
            number /= 10;
        }
        digits.add(number);
        return digits;
    }

    private static boolean listEquals(List<Integer> a, List<Integer> b) {
        if (a.size() != b.size()) {
            return false;
        }
        Collections.sort(a);
        Collections.sort(b);
        return a.equals(b);
    }

    private static boolean testZero() {
        return 0 == find(0);
    }

    private static boolean testNegative() {
        return 0 == find (-10);
    }

    private static boolean testOneDigit() {
        return 8 == find(8);
    }

    private static boolean testHigherExists() {
        return 1243 == find(1234);
    }

    private static boolean testHigherNotExists() {
        return 98765 == find(98765);
    }

    private static boolean testDoubleDigits() {
        return 6995 == find(6959);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testZero()) {
            System.out.println("Zero test failed!");
            counter++;
        }
        if (!testNegative()) {
            System.out.println("Negative test failed!");
            counter++;
        }
        if (!testOneDigit()) {
            System.out.println("One digit test failed!");
            counter++;
        }
        if (!testHigherExists()) {
            System.out.println("Higher exists test failed!");
            counter++;
        }
        if (!testHigherNotExists()) {
            System.out.println("Higher not exists test failed!");
            counter++;
        }
        if (!testDoubleDigits()) {
            System.out.println("Double digits test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed");
    }
}

