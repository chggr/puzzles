import java.util.ArrayList;
import java.util.List;

// Task description: A palindrome is a sequence of digits or characters that
// reads the same backwards as forwards, for example anna or 13431. Write a
// method that takes an integer input and returns the next higher number that
// is also a palindrome. The input number should be greater or equal to 10. If
// it is a number less than 10, it can be defaulted to 10.
//
// E.g. For input -111 the answer is 11
//      For input 0 the answer is 11
//      For input 3 the answer is 11
//      For input 117 the answer is 121
public class NextPalindrome {

    private static int find(int number) {
        if (number < 10) {
            number = 10;
        }

        for (int i = number + 1; ; i++) {
            if (isPalindrome(i)) {
                return i;
            }
        }
    }

    private static boolean isPalindrome(int number) {
        final List<Integer> digits = getDigits(number);

        for (int i = 0; i < digits.size() / 2; i++) {
            if (!digits.get(i).equals(digits.get(digits.size() - i - 1))) {
                return false;
            }
        }
        return true;
    }

    private static List<Integer> getDigits(int number) {
        final List<Integer> digits = new ArrayList<>();
        while (number >= 10) {
            digits.add(number % 10);
            number /= 10;
        }
        digits.add(number);
        return digits;
    }

    private static boolean testZero() {
        return 11 == find(0);
    }

    private static boolean testNegative() {
        return 11 == find(-121);
    }

    private static boolean testOneDigit() {
        return 11 == find(3);
    }

    private static boolean testLargeNumber() {
        return 99888899 == find(99887766);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testZero()) {
            System.out.println("Zero test failed!");
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
        if (!testLargeNumber()) {
            System.out.println("Large number test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}
