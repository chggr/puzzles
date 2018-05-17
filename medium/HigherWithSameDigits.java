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
//
// The second implementation is much more efficient and can compute the next
// higher integer is O(N * logN). Initially we extract all digits of the input
// integer into an array and traverse the array from right to left to identify
// the position of the first digit D that is smaller than the previously
// traversed. We then search the right side for the smallest digit M that is
// also smaller than D. We then swap these two digits and sort all digits on
// the right side to arrive to the final result. The runtime complexity of this
// algorithm is O(N * logN) where N is the number of digits in the input integer
// because of the sorting required at the final step.

public class HigherWithSameDigits {

    private static int[] getHist(int number) {
        int[] hist = new int[10];
        while (number > 0) {
            hist[number % 10]++;
            number /= 10;
        }
        return hist;
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

        int[] hist = getHist(number);
        int count = getDigitCount(number);

        for (int i = number + 1; i < Math.pow(10, count + 1); i++) {
            if (Arrays.equals(hist, getHist(i))) return i;
        }
        return number;
    }

    private static int[] getDigits(int number) {
        int count = getDigitCount(number);
        int[] digits = new int[count];
        for (int i = count - 1; i >= 0; i--) {
            digits[i] = number % 10;
            number /= 10;
        }
        return digits;
    }

    private static int getNumber(int[] digits) {
        int result = 0;
        for (int i = 0; i < digits.length; i++) {
            if (digits[i] < 0) return 0;
            result *= 10;
            result += digits[i];
        }
        return result;
    }

    private static void swap(int[] array, int a, int b) {
        if (a == b) return;
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    private static int find2(int number) {
        if (number <= 0) return 0;
        int[] digits = getDigits(number);

        // Find the position where current digit D is smaller than previous digit.
        int pos = digits.length - 2;
        while (pos >= 0 && digits[pos] >= digits[pos + 1]) pos--;
        if (pos < 0) return number;

        // Search on the right side to find the smallest digit M that is
        // also greater than digit D.
        int min = Integer.MAX_VALUE;
        int minIndex = pos;
        for (int i = minIndex + 1; i < digits.length; i++) {
            if (digits[i] > digits[pos] && digits[i] < min) {
                min = digits[i];
                minIndex = i;
            }
        }
        if (minIndex == pos) return number;

        // Swap digits D with M.
        swap(digits, pos, minIndex);

        // Sort all remaining digits on the right and return the result.
        Arrays.sort(digits, pos + 1, digits.length);
        return getNumber(digits);
    }

    private static boolean testGetHist() {
        return
            Arrays.equals(new int[] {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, getHist(1230)) &&
            Arrays.equals(new int[] {0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, getHist(546)) &&
            Arrays.equals(new int[] {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, getHist(978)) &&
            Arrays.equals(new int[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, getHist(0)) &&
            Arrays.equals(new int[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, getHist(-1));
    }

    private static boolean testGetDigitCount() {
        return 1 == getDigitCount(4) &&
               3 == getDigitCount(528) &&
               8 == getDigitCount(29504518) &&
               0 == getDigitCount(0) &&
               0 == getDigitCount(-1);
    }

    private static boolean testGetDigits() {
        return Arrays.equals(new int[] {7}, getDigits(7)) && 
               Arrays.equals(new int[] {3, 8, 2}, getDigits(382)) &&
               Arrays.equals(new int[] {9, 6, 2, 8, 1}, getDigits(96281)) &&
               Arrays.equals(new int[] {}, getDigits(0)) &&
               Arrays.equals(new int[] {}, getDigits(-1));
    }

    private static boolean testGetNumber() {
        return 0 == getNumber(new int[] {}) &&
               0 == getNumber(new int[] {-1}) &&
               7 == getNumber(new int[] {7}) &&
               396 == getNumber(new int[] {3, 9, 6});
    }

    private static boolean testFind() {
        return 0 == find(0) &&
               0 == find(-10) &&
               8 == find(8) &&
               1243 == find(1234) &&
               9876 == find(9876) &&
               9999 == find(9999) &&
               201 == find(120) &&
               251678 == find(218765);
    }

    private static boolean testFind2() {
        return 0 == find2(0) &&
               0 == find2(-10) &&
               8 == find2(8) &&
               1243 == find2(1234) &&
               9876 == find2(9876) &&
               9999 == find2(9999) &&
               201 == find2(120) &&
               251678 == find2(218765);
    }

    private static boolean testFindBoth() {
        for (int i = 0; i < 10000; i++) {
            if (find(i) != find2(i)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testGetHist()) {
            System.out.println("Get hist test failed!");
            counter++;
        }
        if (!testGetDigitCount()) {
            System.out.println("Get digit count test failed!");
            counter++;
        }
        if (!testGetDigits()) {
            System.out.println("Get digits test failed!");
            counter++;
        }
        if (!testGetNumber()) {
            System.out.println("Get number test failed!");
            counter++;
        }
        if (!testFind()) {
            System.out.println("Find test failed!");
            counter++;
        }
        if (!testFind2()) {
            System.out.println("Find2 test failed!");
            counter++;
        }
        if (!testFindBoth()) {
            System.out.println("Find both test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed");
    }
}

