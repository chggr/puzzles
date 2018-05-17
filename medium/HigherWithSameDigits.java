import java.util.Arrays;

// Task description: Given any positive integer, find the next higher integer
// that uses exactly the same digits. If the given number is negative or zero,
// return zero. In cases where no higher integer with the same digits exists,
// return the number provided.
//
// E.g. For input 1234 the answer is 1243
//      For input -10 the answer is 0
//      For input 0 the answer is 0
//      For input 98765 the answer is 98765
//      For input 120 the answer is 201
//
// Solution: The first implementation below uses a simple brute force approach
// to solve this task. It first calculates the number of digits in the input
// integer and their histogram. It then iterates through all numbers that are
// higher and have the same count of digits to identify one that also has the
// same histogram. The runtime complexity of this approach is O(N * 10^N), where
// N is the number of digits of the given integer. The algorithm potentially
// examines 10^N candidates and for each one extracts and compares its digits.

public class HigherWithSameDigits {

    private static int[] getDigitHist(int number) {
        int[] digits = new int[10];
        while (number > 0) {
            digits[number % 10]++;
            number /= 10;
        }
        return digits;
    }

    private static int getDigitCount(int number) {
        int count = 0;
        while (number > 0) {
            count++;
            number /= 10;
        }
        return count;
    }

    private static int find(int number) {
        if (number <= 0) return 0;

        int[] hist = getDigitHist(number);
        int count = getDigitCount(number);

        for (int i = number + 1; i < Math.pow(10, count + 1); i++) {
            if (Arrays.equals(hist, getDigitHist(i))) return i;
        }
        return number;
    }

    private static boolean testGetDigitHist() {
        int[] expected = {1, 1, 1, 0, 1, 2, 0, 0, 1, 1};
        return Arrays.equals(expected, getDigitHist(25051984));
    }

    private static boolean testGetDigitCount() {
        return 0 == getDigitCount(0) &&
               1 == getDigitCount(4) &&
               3 == getDigitCount(528) &&
               8 == getDigitCount(25051984);
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
        if (!testGetDigitHist()) {
            System.out.println("Get digit hist test failed!");
            counter++;
        }
        if (!testGetDigitCount()) {
            System.out.println("Get digit count test failed!");
            counter++;
        }
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

