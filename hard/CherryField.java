// Task description: Given an N x N matrix that represents a cherry field, each
// position can be populated either with 0 when there are no cherries or with 1
// where there is one cherry. Write a method to find the maximum number of
// cherries that can be collected when a picker starts at position [0, 0] and
// reaches position [N - 1, N - 1] by moving right or down and then returns back
// by moving left or up.
//
// E.g. for the following cherry field:
//
//           {{1, 1, 1, 0, 0},
//            {0, 0, 1, 0, 1},
//            {1, 0, 1, 0, 0},
//            {0, 0, 1, 0, 0},
//            {0, 0, 1, 1, 1}}
//
//       the method should return 11
//
// Solution: Instead of having just one picker start from top left, go to the
// bottom right and return, we can simplify the problem by considering two
// pickers starting from top right and moving to bottom left. The aim is to
// find a path for each picker so that the maximum number of cherries overall
// is collected.
//
// A simple approach would be to use a greedy dynamic programming algorithm to
// find the most cherries we can pick up with one path, pick them up and then
// find the most cherries we can pick up with a second path on the remaining
// field. This approach would work in many cases, but unfortunately in some
// cases like the example above it gives incorrect results. The first pass
// would pick up 9 cherries and the second path 1 cherry giving a maximum of
// 10 cherries when the correct answer is actually 11.
//
// The first implementation below uses a recursive approach to move both cherry
// pickers at the same time and return the maximum number of cherries both can
// pick up. The runtime complexity of this approach is O(4 ^ N) because there
// are four recursive branches and the recursion depth is proportional to N. The
// space complexity is O(N) for the recursive stack.
//
// We can use memoization to trade off space for time by allocating a 4D matrix
// to store and reuse intermediate results. This would reduce the runtime
// complexity to O(N ^ 4) since there are N ^ 4 positions to fill in the memo
// matrix. The space complexity would also be O(N ^ 4) for the memo matrix.
//
// We can reduce the space complexity further by noticing that after S steps,
// our first picker will be at [rowA, colA] and our second picker would be at
// [rowB, colB]. Both of them would have travelled S steps so we just need three
// rather than four variables to store their position: [rowA, colA, colB]. Then
// rowB can be derived as rowA + colA - colB. This means that our memoization
// matrix above does not need to be a 4D matrix but can really be reduced to 3D.
// Therefore this drops both the space and runtime complexities to O(N ^ 3). The
// four possible moves can now be encoded as:
//
// (1) Picker A down, picker B down => memo[rowA + 1][colA][colB]
// (2) Picker A right, picker B down => memo[rowA][colA + 1][colB]
// (3) Picker A down, picker B right => memo[rowA + 1][colA][colB + 1]
// (4) Picker A right, picker B right => memo[rowA][colA + 1][colB + 1]

public class CherryField {

    private static int max(int a, int b, int c, int d) {
        return Math.max(Math.max(a, b), Math.max(c, d));
    }

    private static int pick(int[][] field,
                            int rowA, int colA,
                            int rowB, int colB) {

        if (rowA >= field.length ||
            rowB >= field.length ||
            colA >= field[0].length ||
            colB >= field[0].length) return 0;

        // Return the maximum number of cherries picked when we consider all
        // possible moves for the two pickers. If the pickers are on the same
        // position, we need to avoid picking the same cherry twice.
        return field[rowA][colA] +
               (rowA != rowB && colA != colB ? field[rowB][colB] : 0) +
            max(pick(field, rowA + 1, colA, rowB + 1, colB),
                pick(field, rowA + 1, colA, rowB, colB + 1),
                pick(field, rowA, colA + 1, rowB + 1, colB),
                pick(field, rowA, colA + 1, rowB, colB + 1));
    }

    private static int pick_memo(int[][] field, int[][][] memo,
                                 int rowA, int colA, int colB) {

        int rowB = rowA + colA - colB;
        if (rowA >= field.length ||
            rowB >= field.length ||
            colA >= field[0].length ||
            colB >= field[0].length) return 0;

        if (memo[rowA][colA][colB] != -1) return memo[rowA][colA][colB];

        int cherries = field[rowA][colA] +
                       (rowA != rowB && colA != colB ? field[rowB][colB] : 0) +
                    max(pick_memo(field, memo, rowA + 1, colA, colB),
                        pick_memo(field, memo, rowA + 1, colA, colB + 1),
                        pick_memo(field, memo, rowA, colA + 1, colB),
                        pick_memo(field, memo, rowA, colA + 1, colB + 1));
        memo[rowA][colA][colB] = cherries;
        return cherries;
    }

    private static int pick_memo(int[][] field) {
        int rows = field.length;
        int cols = field[0].length;

        int[][][] memo = new int[rows][cols][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < cols; k++) {
                    memo[i][j][k] = -1;
                }
            }
        }
        return pick_memo(field, memo, 0, 0, 0);
    }

    private static boolean testMax() {
        return 4 == max(1, 2, 3, 4) &&
              -1 == max(-1, -2, -3, -4) &&
               5 == max(5, 3, -2, -10);
    }

    private static boolean testPickEmpty() {
        int[][] field = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
        return 0 == pick(field, 0, 0, 0, 0) &&
               0 == pick_memo(field);
    }

    private static boolean testPickFull() {
        int[][] field = {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1}};
        return 16 == pick(field, 0, 0, 0, 0) &&
               16 == pick_memo(field);
    }

    private static boolean testPick() {
        int[][] field = {
            {1, 1, 1, 0, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 1}};
        return 11 == pick(field, 0, 0, 0, 0) &&
               11 == pick_memo(field);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testMax()) {
            counter++;
            System.out.println("Max test failed");
        }
        if (!testPickEmpty()) {
            counter++;
            System.out.println("Pick empty test failed");
        }
        if (!testPickFull()) {
            counter++;
            System.out.println("Pick full test failed");
        }
        if (!testPick()) {
            counter++;
            System.out.println("Pick test failed");
        }
        System.out.println(counter + " tests failed.");
    }
}

