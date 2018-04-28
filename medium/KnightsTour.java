// Task description: A knight is placed on the first block of an empty board and
// moves following the rules of chess. It must visit all squares exactly once,
// write a method to return whether a tour is possible and populate the board
// with the moves required to reach each position.
//
// E.g. for a 6x6 board a possible solutions is:
//      {{ 1,  12,  21,  28,   7,  10},
//       {22,  29,   8,  11,  20,  27},
//       {13,   2,  23,   4,   9,   6},
//       {30,  35,  32,  17,  26,  19},
//       {33,  14,   3,  24,   5,  16},
//       {36,  31,  34,  15,  18,  25}}
//
// Solution: The recursive implementation below uses backtracking to identify
// whether a tour is possible. In each recursive call, it first checks whether
// the given position is valid (i.e. within the board and not visited before)
// and returns false if not. It subsequently places the knight at that position
// and if the board is full returns true. Otherwise it continues moving the
// knight recursively until a valid solution has been found.
//
// Using backtracking, we back up only as far as needed to reach a previous
// decision point with an (as yet) unexplored alternative. Eventually more and
// more of these decision points will have been fully explored and the method
// will need to backtrack further and further. If we backtrack all the way to
// our initial position, then all possible alternatives will have been explored
// and we can conclude that the problem is unsolvable. In that case we will
// have done all the work of the exhaustive recursion and know that there is
// no viable solution possible.

public class KnightsTour {

    // Possible moves for a knight in a chess board.
    private static final int[] MOVES_ROW = {2, 2, -2, -2, 1, -1, 1, -1};
    private static final int[] MOVES_COL = {1, -1, 1, -1, 2, 2, -2, -2};

    public static boolean isFull(int[][] board) {
        boolean full = true;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                if (board[i][j] == 0) {
                    full = false;
                    break;
                }
            }
        }
        return full;
    }

    public static void print(int[][] board) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                System.out.print(String.format("%2d  ", board[i][j]));
            }
            System.out.println();
        }
    }

    // A position is valid if it is within the board and has not been visited.
    public static boolean isValid(int[][] board, int row, int col) {
        return row >= 0 && col >= 0 && row < board.length &&
               col < board[0].length && board[row][col] == 0;
    }

    public static boolean tour(int[][] board, int row, int col, int moves) {
        if (!isValid(board, row, col)) return false;

        board[row][col] = moves;
        if (isFull(board)) return true;

        for (int i = 0; i < 8; i++) {
            if (tour(board, row + MOVES_ROW[i], col + MOVES_COL[i], moves + 1)) {
                return true;
            }
        }
        board[row][col] = 0; // backtrack
        return false;
    }

    public static boolean testUnsolvable() {
        int[][] board = new int[2][20];
        return !tour(board, 0, 0, 1);
    }

    public static boolean testSolvable() {
        int[][] board = new int[6][6];
        return tour(board, 0, 0, 1);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testUnsolvable()) {
            counter++;
            System.out.println("Unsolvable board test failed!");
        }
        if (!testSolvable()) {
            counter++;
            System.out.println("Solvable board test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

