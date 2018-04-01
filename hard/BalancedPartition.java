import static java.util.Arrays.asList;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

// Task description: Given an array of positive integers, partition them into
// two subsets so that the sum of elements in each subset is equal to the other.
//
// E.g. for input array: {3, 1, 1, 2, 1}
//      the two subsets are: {3, 1} and {1, 2, 1}
//
//      for input array: {3, 1, 2, 2, 1}
//      the method should return null
//
// Solution: The first implementation below partitions the input array using
// an iterative approach. It constructs all possible subsets / partitions and
// checks each combination for sum equality. The runtime complexity of this
// approach is O(2^N) and space complexity is O(1).
//
// The second implementation is similar to the first but uses a recursive
// approach to identify and examine all possible partitions. There are two
// options for each element in the input array: it can either be part of the
// first subset or part of the second subset. The recursive method initially
// adds the element to the first subset and then to the second subset, calling
// itself recursively to verify whether a solution has been found. The runtime
// complexity of this approach is again O(2^N) because the method is called
// twice in each recursive step. The space complexity is O(N) because recursion
// will store up to N frames in the stack.
//
// The third implementation uses dynamic programming to partition the input
// array. We first calculate the sum of all elements in the array and check that
// it is even. If the sum is odd, then there is no way to partition the array.
// We then create a memo array of size sum / 2 + 1 and fill it with -1. The memo
// array will be populated at index j only if there is a subset of elements in
// the input array whose sum is j. It will be populated with the index in the
// input array of the last element that was added to reach that sum. This allows
// us to trace back the elements and construct the subset that gave the required
// sum.
//
// In more detail, we go through all elements in the input array. For each
// element i, we traverse the memo array backwards, checking whether each
// position can be filled. If a given position j is already filled, we skip it.
// If it is not filled (i.e. it is populated with -1) then we can only fill it
// if there is already a subset in the input array with sum j - array[i]. If
// such a subset exists, then memo[j - array[i]] will also have been filled.
// Therefore in this case we can fill memo[j] with i, i.e. the index of the
// element in the input array that has been added to the previous subset to
// give us a total sum of j. The runtime complexity of this approach is O(M*N),
// where M is the size of the memo array and N is the size of the input array.
// The space complexity is O(M).

public class BalancedPartition {

    private static final class Pair {
        List<Integer> one;
        List<Integer> two;

        public Pair(List<Integer> one, List<Integer> two) {
            this.one = one;
            this.two = two;
        }
    }

    private static int sum(List<Integer> list) {
        return list.stream().mapToInt(Integer::intValue).sum();
    }

    private static Pair partition_iter(int[] array) {
        List<Integer> one = new ArrayList<>();
        List<Integer> two = new ArrayList<>();

        for (int i = 1; i < Math.pow(2, array.length) - 1; i++) {
            one.clear();
            two.clear();

            int index = 0;
            while (index < array.length) {
                if ((i & (1 << index)) != 0) {
                    one.add(array[index]);
                } else {
                    two.add(array[index]);
                }
                index++;
            }

            if (sum(one) == sum(two)) {
                return new Pair(one, two);
            }
        }
        return null;
    }

    private static boolean partition_rec(int[] array, int index,
                                         List<Integer> one,
                                         List<Integer> two) {
        if (index >= array.length) {
            return !one.isEmpty() &&
                   !two.isEmpty() &&
                   sum(one) == sum(two);
        }

        // Attempt to add to the first set.
        one.add(array[index]);
        if (partition_rec(array, index + 1, one, two)) return true;
        one.remove(one.size() - 1);

        // Attempt to add to the second set.
        two.add(array[index]);
        if (partition_rec(array, index + 1, one, two)) return true;
        two.remove(two.size() - 1);

        return false;
    }

    public static Pair partition_rec(int[] array) {
        Pair pair = new Pair(new ArrayList<>(), new ArrayList<>());
        if (partition_rec(array, 0, pair.one, pair.two)) return pair;
        return null;
    }

    private static Pair partition_dyn(int[] array) {

        // Calculate sum of elements, cannot partition if odd.
        int sum = 0;
        for (int value : array) {
            sum += value;
        }
        if (sum % 2 != 0) return null;

        // Initialize memo array, fill with -1.
        int[] memo = new int[sum / 2 + 1];
        for (int i = 0; i < memo.length; i++) memo[i] = -1;

        // Go through input array, filling up memo.
        for (int i = 0; i < array.length; i++) {
            for (int j = memo.length - 1; j > 0; j--) {
                if (memo[j] != -1) continue;
                if (j - array[i] < 0) continue;
                if (j - array[i] == 0 ||
                    memo[j - array[i]] != -1) memo[j] = i;
            }
        }

        // Have not reached sum / 2, unable to partition.
        if (memo[sum / 2] == -1) return null;

        // Extract indices of elements in partition.
        Set<Integer> indices = new HashSet<>();
        int index = sum / 2;
        while (memo[index] != -1) {
            indices.add(memo[index]);
            index -= array[memo[index]];
        }

        // Build and return the two partitions.
        List<Integer> one = new ArrayList<>();
        List<Integer> two = new ArrayList<>();
        for (int i = 0; i < array.length; i++) {
            if (indices.contains(i)) {
                one.add(array[i]);
            } else {
                two.add(array[i]);
            }
        }
        return new Pair(one, two);
    }

    public static boolean testEmptyArray() {
        int[] array = new int[0];

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return null == iter && null == rec && null == dyn;
    }

    public static boolean testOneElement() {
        int[] array = new int[] { 1 };

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return null == iter && null == rec && null == dyn;
    }

    public static boolean testOdd_NoPartition() {
        int[] array = new int[] {3, 1, 1, 2, 2};

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return null == iter && null == rec && null == dyn;
    }

    public static boolean testOdd_Partition() {
        int[] array = new int[] {3, 1, 1, 2, 1};

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return iter.one.equals(asList(3, 1)) &&
               iter.two.equals(asList(1, 2, 1)) &&
               rec.one.equals(asList(3, 1)) &&
               rec.two.equals(asList(1, 2, 1)) &&
               dyn.one.equals(asList(3, 1)) &&
               dyn.two.equals(asList(1, 2, 1));
    }

    public static boolean testEven_NoPartition() {
        int [] array = new int[] {3, 1, 2, 2, 2, 1};

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_rec(array);

        return null == iter && null == rec && null == dyn;
    }

    public static boolean testEven_Partition() {
        int [] array = new int[] {3, 1, 1, 2, 2, 1};

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return iter.one.equals(asList(3, 1, 1)) &&
               iter.two.equals(asList(2, 2, 1)) &&
               rec.one.equals(asList(3, 1, 1)) &&
               rec.two.equals(asList(2, 2, 1)) &&
               dyn.one.equals(asList(3, 1, 1)) &&
               dyn.two.equals(asList(2, 2, 1));
    }

    public static boolean testLarge() {
        int [] array = new int[] {100, 1, 2, 3};

        Pair iter = partition_iter(array);
        Pair rec = partition_rec(array);
        Pair dyn = partition_dyn(array);

        return null == iter && null == rec && null == dyn;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmptyArray()) {
            counter++;
            System.out.println("Empty array test failed!");
        }
        if (!testOneElement()) {
            counter++;
            System.out.println("One element array test failed!");
        }
        if (!testOdd_NoPartition()) {
            counter++;
            System.out.println("Odd elements, no partition test failed!");
        }
        if (!testOdd_Partition()) {
            counter++;
            System.out.println("Odd elements partition test failed!");
        }
        if (!testEven_NoPartition()) {
            counter++;
            System.out.println("Even elements, no partition test failed!");
        }
        if (!testEven_Partition()) {
            counter++;
            System.out.println("Even elements partition test failed!");
        }
        if (!testLarge()) {
            counter++;
            System.out.println("Large element partition test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

