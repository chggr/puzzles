import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// Task description: Given a knapsack that can carry up to W grams and a set of
// items, each with its own weight and value, write a method to determine which
// items to take so that they fit in the knapsack and their total value is as
// large as possible.
//
// E.g. Given the following items:      if the knapsack can carry up to 10
//      weight:  5   4   6   3          the method should return {1, 3} to
//      value:  10  40  30  50          achieve maximum value: 90
//
// Solution: This is a combinatorial optimization problem, where we need to
// optimize for both the weight and value of the items. The first implementation
// below is brute force. It goes through all possible combinations of the given
// items and identifies the combination with the greatest value whose total
// weight is less than the given limit. The runtime complexity of this approach
// is O(2 ^ N), where N is the number of items.
//
// The second implementation uses dynamic programming to arrive to the solution
// more efficiently. We first define a memo array to memoize the results of sub
// problems and thus speed up execution. We store in memo[i][w] the maximum
// value that can be attained with weight less than or equal to w using only the
// first i items. The memo array can be filled in recursively using the logic
// below:
//
// - memo[0][w] = 0
// - memo[i][w] = memo[i - 1][w] if w < w[i]
// - memo[i][w] = max(memo[i - 1][w], memo[i - 1][w - w[i]] + v[i]
//
// The first row of memo will always be populated with zeros since there are no
// available items on that row (i = 0). For all subsequent positions, we first
// check whether the current column (w) is large enough to allow us to add the
// item (i). If it is not large enough, then we simply copy the value achieved
// without this item (i.e. memo[i][w] = memo[i - 1][w]). On the contrary, if it
// is large enough we need to calculate the best value we can achieve with and
// without the current item and take the maximum. The value we can achieve
// without this item will be memo[i - 1][w]. The value we can achieve with the
// item would be memo[i - 1][w - w[i]] + v[i]. We basically add the value of
// the item to the best value we achieved previously with the same weight minus
// the weight of the item.
//
// Both the runtime and space complexity of this approach is O(N * W), where N
// is the number of items and W is the maximum weight the knapsack can carry.
// Note that we also use a "keep" array of booleans to store whether we have
// decided to take the i item in memo[i][w]. This allows us to reconstruct the
// output at the end.

public class Knapsack {

    // Converts the given number into a list of integers containing
    // the positions where bits are set in its binary representation.
    private static List<Integer> numberToList(int num) {
        List<Integer> result = new ArrayList<>();
        int index = 0;
        while (num != 0) {
            if (num % 2 == 1) result.add(index);
            index++;
            num /= 2;
        }
        return result;
    }

    private static List<Integer> knapsack_iter(int[] weight,
                                               int[] value,
                                               int capacity) {

        int maxValue = 0;
        int bestCombination = 0;

        for (int i = 0; i < Math.pow(2, weight.length); i++) {
            int currWeight = 0;
            int currValue = 0;
            for (int j = 0; j < weight.length; j++) {
                if ((i & (1 << j)) != 0) {
                    currWeight += weight[j];
                    currValue += value[j];
                }
            }

            if (currWeight > capacity) continue;
            if (currValue > maxValue) {
                maxValue = currValue;
                bestCombination = i;
            }
        }
        return numberToList(bestCombination);
    }

    private static List<Integer> knapsack_dyn(int[] weight,
                                              int[] value,
                                              int capacity) {

        int[][] memo = new int[weight.length + 1][capacity];
        boolean[][] keep = new boolean[weight.length + 1][capacity];

        // Fill in the memo and keep arrays for every available item.
        for (int i = 1; i <= weight.length; i++) {
            for (int j = 0; j < capacity; j++) {

                // There is not enough capacity to take this item.
                if (weight[i - 1] > j) {
                    memo[i][j] = memo[i - 1][j];
                    continue;
                }

                // Calculate the value of taking or leaving the item.
                int without = memo[i - 1][j];
                int with = value[i - 1] + memo[i - 1][j - weight[i - 1]];
                if (with > without) {
                    memo[i][j] = with;
                    keep[i][j] = true;
                } else {
                    memo[i][j] = without;
                }
            }
        }

        List<Integer> result = new ArrayList<>();
        int index = capacity - 1;
        for (int i = weight.length; i >= 1 && index >= 0; i--) {
            if (keep[i][index]) {
                result.add(0, i - 1);
                index -= weight[i - 1];
            }
        }
        return result;
    }

    private static boolean testZeroCapacity() {
        int[] weight = new int[] {5, 4, 6, 3};
        int[] value = new int[] {10, 40, 30, 50};

        List<Integer> iter = knapsack_iter(weight, value, 0);
        List<Integer> dyn = knapsack_dyn(weight, value, 0);

        return iter.isEmpty() && dyn.isEmpty();
    }

    private static boolean testKnapsack() {
        int[] weight = new int[] {5, 4, 6, 3};
        int[] value = new int[] {10, 40, 30, 50};

        List<Integer> iter = knapsack_iter(weight, value, 10);
        List<Integer> dyn = knapsack_dyn(weight, value, 10);

        return iter.equals(Arrays.asList(1, 3)) &&
               dyn.equals(Arrays.asList(1, 3));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testZeroCapacity()) {
            counter++;
            System.out.println("Zero capacity test failed.");
        }
        if (!testKnapsack()) {
            counter++;
            System.out.println("Knapsack test failed.");
        }
        System.out.println(counter + " tests failed.");
    }
}

