// Task description: Given a two dimensional matrix that contains only ones and
// zeros, write a method to return the maximum size square sub-matrix where all
// elements are set to one.
//
// E.g. for matrix:
//                    {{0, 0, 1, 0, 0},
//                     {1, 0, 0, 1, 0},
//                     {0, 1, 1, 1, 1},
//                     {1, 0, 1, 1, 0},
//                     {0, 1, 0, 0, 1}}
//
//      the method should return: 2
//
// Solution: The brute force approach would be to go through all elements of the
// input matrix and attempt to identify whether there exists a square of ones
// with that element as the top left corner. This approach would take O(N ^ 5):
// O(N ^ 2) to go through all elements of the matrix, a further O(N) to explore
// all squares based on that element and a final O(N ^ 2) to validate whether
// each square contains only ones. The space complexity of this approach would
// be O(1) as no extra space is used.
//
// The implementation below uses a dynamic programming approach to calculate the
// maximum square matrix in just O(N ^ 2) time and space complexity. We first
// define an N x N memo matrix to hold at each position the size of the square
// sub-matrix with all ones where that element is at the bottom right of the
// sub-matrix. The memo matrix is then populated based on the data in the input
// matrix as follows:
//
// (a) if the element is zero, no sub-matrix can be formed with that element at
//     the bottom right corner and thus memo is populated with zero.
//
// (b) if the element is one, memo is populated as the minimum of the memo
//     values at [row - 1][col] / [row][col -1] / [row - 1][col - 1] of the memo
//     matrix plus one.
//
// At the end we go through the memo matrix to pick up and return the maximum.

public class MaxSquareSubmatrix {

    private static int maxSquareSubmatrix(int[][] matrix) {
        if (matrix == null ||
            matrix.length == 0 ||
            matrix[0].length == 0) return 0;

        int rows = matrix.length;
        int cols = matrix[0].length;

        int[][] memo = new int[rows][cols];
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (matrix[row][col] == 0) continue;

                int min = Integer.MAX_VALUE;
                if (row > 0 && memo[row - 1][col] < min) min = memo[row - 1][col];
                if (col > 0 && memo[row][col - 1] < min) min = memo[row][col - 1];
                if (col > 0 && row > 0 && memo[row - 1][col - 1] < min)
                    min = memo[row - 1][col - 1];
                memo[row][col] = min == Integer.MAX_VALUE ? 1 : min + 1;
            }
        }

        int max = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (memo[row][col] > max) max = memo[row][col];
            }
        }
        return max;
    }

    private static boolean testNull() {
        return 0 == maxSquareSubmatrix(null);
    }

    private static boolean testEmpty() {
        return 0 == maxSquareSubmatrix(new int[0][0]) &&
               0 == maxSquareSubmatrix(new int[0][1]) &&
               0 == maxSquareSubmatrix(new int[1][0]);
    }

    private static boolean testZeroMatrix() {
        return 0 == maxSquareSubmatrix(new int[][] {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}});
    }

    private static boolean testOneMatrix() {
        return 5 == maxSquareSubmatrix(new int[][] {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1}});
    }

    private static boolean testSubMatrix() {
        return 2 == maxSquareSubmatrix(new int[][] {
            {0, 0, 1, 0, 0},
            {1, 0, 0, 1, 0},
            {0, 1, 1, 1, 1},
            {1, 0, 1, 1, 0},
            {0, 1, 0, 0, 1}});
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNull()) {
            counter++;
            System.out.println("Null test failed!");
        }
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty test failed!");
        }
        if (!testZeroMatrix()) {
            counter++;
            System.out.println("Zero matrix test failed!");
        }
        if (!testOneMatrix()) {
            counter++;
            System.out.println("One matrix test failed!");
        }
        if (!testSubMatrix()) {
            counter++;
            System.out.println("Sub matrix test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

