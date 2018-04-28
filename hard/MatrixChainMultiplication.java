// Task description: Given a sequence of matrices, find the most efficient way
// to multiply them to achieve the minimum number of operations. The dimensions
// of these matrices are given as an array of integers.
//
// E.g. The following input dimensions {1, 2, 3, 4} represent three matrices:
//      A {1, 2}  /  B {2, 3}  /  C {3, 4}
//
//      The cost of (A * B) * C is 1 * 2 * 3 + 1 * 3 * 4 = 6 + 12 = 18
//      The cost of A * (B * C) is 1 * 2 * 4 + 2 * 3 * 4 = 8 + 24 = 32
//      The method should return 18.
//
// Solution: One possible approach would be to go through the input array of
// dimensions and calculate the number of operations required to multiply each
// pair of matrices. Then greedily choose the minimum of these and repeat the
// process until the total cost is calculated. Unfortunately this greedy
// approach does not work in many cases, such as {2, 1, 2, 5}. In this case the
// greedy algorithm would first choose to multiply {2, 1} and {1, 2} at a cost
// of 4 and then the resulting {2, 2} and {2, 5} at a cost of 20 for a total
// cost of 24 operations. The correct answer though is to first multiply {1, 2}
// with {2, 5} at a cost of 10 and then {1, 2} with the resulting {2, 5} at a
// cost of 10, giving a total cost of just 20 operations.
//
// The first implementation below uses a recursive algorithm to calculate the
// minimum number of operations required to multiply the given matrices. It
// attempts to place parenthesis at all possible positions and calls itself
// recursively to calculate the total cost of each placement. It keeps track
// and returns the minimum cost. The runtime complexity of this approach is
// O(2 ^ N) where N is the number of matrices, because at each recursion the
// method calls itself twice. The space complexity is O(N) required for the
// execution stack.
//
// The second implementation uses a memoization matrix to improve the runtime
// complexity of the simple recursive approach. This allows us to store and
// reuse any intermediate results and therefore reduce the runtime complexity
// to O(N ^ 3). This is of course done at the expense of space complexity, which
// has now increased to O(N ^ 2). The runtime complexity can be derived if we
// consider that we need to populate all positions in the N * N array and for
// each one we execute a for loop N times to calculate the minimum cost.
//
// Finally, the third implementation uses a dynamic programming approach to
// calculate the results of overlapping sub-problems in a bottom up fashion.
// A memoization array is defined and populated from the diagonal outwards using
// the same formula as before. The runtime complexity of this algorithm is again
// O(N ^ 3) and space complexity is O(N ^ 2).

public class MatrixChainMultiplication {

    // Matrix Mi has dimensions dim[i-1] x dim[i]
    private static int cost_rec(int[] dim, int from, int to) {
        if (to == from) return 0;

        // Go through the array, placing parentheses at all possible
        // positions and recursively calculating the total cost.
        int result = Integer.MAX_VALUE;
        for (int i = from; i < to; i++) {

            // Total cost = [cost of multiplying all matrices on the left] +
            //              [cost of multiplying all matrices on the right] +
            //              [cost of multiplying the two resulting matrices]
            int temp = cost_rec(dim, from, i) +
                       cost_rec(dim, i + 1, to) +
                       dim[from - 1] * dim[i] * dim[to];

            if (temp < result) result = temp;
        }
        return result;
    }

    // Similar to implementation above, but uses a memoization matrix to
    // store and reuse intermediate results and improve runtime complexity.
    private static int cost_memo(int[] dim, int from, int to, int[][] memo) {
        if (to == from) return 0;
        if (memo[from][to] != 0) return memo[from][to];

        int result = Integer.MAX_VALUE;
        for (int i = from; i < to; i++) {
            int temp = cost_memo(dim, from, i, memo) +
                       cost_memo(dim, i + 1, to, memo) +
                       dim[from - 1] * dim [i] * dim[to];

            if (temp < result) result = temp;
        }
        memo[from][to] = result;
        return result;
    }

    private static int cost_memo(int[] dim) {
        int[][] memo = new int[dim.length][dim.length];
        return cost_memo(dim, 1, dim.length - 1, memo);
    }

    // Similar to memoization implementation above, but calculates results
    // to sub-problems iteratively to reduce space requirement.
    private static int cost_dyn(int[] dim) {
        if (dim.length <= 2) return 0;
        int[][] memo = new int[dim.length][dim.length];

        for (int len = 2; len < dim.length; len++) {
            for (int from = 1; from < dim.length - len + 1; from++) {
                int to = from + len - 1;
                memo[from][to] = Integer.MAX_VALUE;
                for (int i = from; i < to; i++) {
                    int temp = memo[from][i] +
                               memo[i + 1][to] +
                               dim[from - 1] * dim[i] * dim[to];
                    if (temp < memo[from][to]) memo[from][to] = temp;
                }
            }
        }
        return memo[1][dim.length - 1];
    }

    private static boolean testOneArray() {
        int[] dim = {1, 2};
        return 0 == cost_rec(dim, 1, 1) &&
               0 == cost_memo(dim) &&
               0 == cost_dyn(dim);
    }

    private static boolean testTwoArrays() {
        int[] dim = {1, 2, 3};
        return 6 == cost_rec(dim, 1, 2) &&
               6 == cost_memo(dim) &&
               6 == cost_dyn(dim);
    }

    private static boolean testThreeArrays() {
        int[] dim = {1, 2, 3, 4};
        return 18 == cost_rec(dim, 1, 3) &&
               18 == cost_memo(dim) &&
               18 == cost_dyn(dim);
    }

    private static boolean testManyArrays() {
        int[] dim = {10, 30, 5, 60};
        return 4500 == cost_rec(dim, 1, 3) &&
               4500 == cost_memo(dim) &&
               4500 == cost_dyn(dim);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testOneArray()) {
            counter++;
            System.out.println("One array test failed!");
        }
        if (!testTwoArrays()) {
            counter++;
            System.out.println("Two arrays test failed!");
        }
        if (!testThreeArrays()) {
            counter++;
            System.out.println("Three arrays test failed!");
        }
        if (!testManyArrays()) {
            counter++;
            System.out.println("Many arrays test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

