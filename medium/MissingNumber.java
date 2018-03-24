import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

// Task description: Given an array that contains all integers for 0 to n except
// from one number, write a method to find the missing number. The array does
// not allow accessing the entire integer in a single operation. We can only
// access one bit of each integer at a time, an operation which takes constant
// time. Can this be done in O(n)?
//
// Solution: A naive implementation would be to calculate the sum of all numbers
// in the array and then derive the missing number taking into account that the
// expected sum should be n * (n + 1) / 2. The runtime complexity of this
// approach is O(n * logn) because we would need to go through n numbers in the
// array, each one having a length of log(n) on average.
//
// The implementation below follows a similar approach but leverages the bit
// values more directly. It recursively checks each bit position and counts the
// numbers in the array that have this bit set to one or zero. If the number of
// ones is greater or equal to the number of zeros, then the missing number will
// have that bit set to zero. Otherwise it will have that bit set to one. At
// each recursion, approximately half of the numbers are eliminated. Therefore
// the total runtime complexity is n + n/2 + n/4 +... = O(n).
//
// The aforementioned approach is based on the observation that in a list of
// numbers from 0 to n we expect there to be the same number of zeros as ones if
// n is odd or an additional zero if n is even. Therefore the count of zeros
// should always be greater than or equal to the count of ones. When a number
// in that list is removed, this balance is disrupted and this allows us to
// identify the missing number.

public class MissingNumber {

    private static BigInteger findMissing(List<BigInteger> nums, int bit) {
        if (nums.isEmpty()) return BigInteger.ZERO;

        List<BigInteger> zeros = new ArrayList<>(nums.size() / 2);
        List<BigInteger> ones = new ArrayList<>(nums.size() / 2);

        for (BigInteger num : nums) {
            if (num.testBit(bit)) {
                ones.add(num);
            } else {
                zeros.add(num);
            }
        }

        if (ones.size() >= zeros.size()) {
            return findMissing(zeros, bit + 1);
        } else {
            return findMissing(ones, bit + 1).setBit(bit);
        }
    }

    private static List<BigInteger> generate(int num, int missing) {
        List<BigInteger> result = new ArrayList<>();
        for (int i = 0; i <= num; i++) {
            if (i == missing) continue;
            result.add(BigInteger.valueOf(i));
        }
        return result;
    }

    private static boolean testMissing() {
        List<BigInteger> nums = generate(10, 3);
        BigInteger result = findMissing(nums, 0);
        return 3 == result.intValue();
    }

    private static boolean testMissingLarge() {
        List<BigInteger> nums = generate(1000000, 9999);
        BigInteger result = findMissing(nums, 0);
        return 9999 == result.intValue();
    }

    private static boolean testNotMissing() {
        List<BigInteger> nums = generate(10, 0);
        BigInteger result = findMissing(nums, 0);
        return 0 == result.intValue();
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testMissing()) {
            counter++;
            System.out.println("Missing test failed!");
        }
        if (!testMissingLarge()) {
            counter++;
            System.out.println("Large missing test failed!");
        }
        if (!testNotMissing()) {
            counter++;
            System.out.println("Not missing test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

