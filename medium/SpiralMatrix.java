import java.util.Arrays;

// Task description: Given a two dimensional matrix containing integers, write
// a method to return an array with the elements in spiral order.
//
// E.g. for matrix: {{1, 2, 3},    the method should return:
//                   {8, 9, 4},    {1, 2, 3, 4, 5, 6, 7, 8, 9}
//                   {7, 6, 5}}

public class SpiralMatrix {

    private static int[] spiral(int[][] matrix) {
        if (matrix == null || matrix.length == 0) return null;

        int rows = matrix.length;
        int cols = matrix[0].length;
        int[] res = new int[rows * cols];

        int idx = 0;
        for (int i = 0; i < (Math.min(rows, cols) + 1) / 2; i++) {

            for (int col = i; col < cols - i; col++) {
                res[idx++] = matrix[i][col];
            }

            for (int row = i + 1; row < rows - i; row++) {
                res[idx++] = matrix[row][cols - i - 1];
            }

            if (i < rows / 2) {
                for (int col = cols - i - 2; col >= i; col--) {
                    res[idx++] = matrix[rows - i - 1][col];
                }
            }

            if (i < cols / 2) {
                for (int row = rows - i - 2; row > i; row--) {
                    res[idx++] = matrix[row][i];
                }
            }
        }
        return res;
    }

    private static boolean testNull() {
        return null == spiral(null);
    }

    private static boolean testEmpty() {
        return null == spiral(new int[0][0]);
    }

    private static boolean testOneElement() {
        int[][] matrix = {{1}};
        int[] expected = {1};

        int[] result = spiral(matrix);
        return Arrays.equals(result, expected);
    }

    private static boolean testOneRow() {
        int[][] matrix = {{1, 2, 3, 4, 5}};
        int[] expected = {1, 2, 3, 4, 5};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testTwoRows() {
        int[][] matrix = {{1, 2, 3, 4, 5},
                          {10, 9, 8, 7, 6}};
        int[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testOneColumn() {
        int[][] matrix = {{1}, {2}, {3}, {4}, {5}};
        int[] expected = {1, 2, 3, 4, 5};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testTwoColumns() {
        int[][] matrix = {{1, 2}, {10, 3}, {9, 4}, {8, 5}, {7, 6}};
        int[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testSquareMatrix() {
        int[][] matrix = {{ 1,  2,  3,  4, 5},
                          {16, 17, 18, 19, 6},
                          {15, 24, 25, 20, 7},
                          {14, 23, 22, 21, 8},
                          {13, 12, 11, 10, 9}};
        int[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                          11, 12, 13, 14, 15, 16, 17, 18,
                          19, 20, 21, 22, 23, 24, 25};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testHorizontalMatrix() {
        int[][] matrix = {{ 1,  2,  3,  4, 5},
                          {12, 13, 14, 15, 6},
                          {11, 10, 9, 8, 7}};
        int[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9,
                          10, 11, 12, 13, 14, 15};
        return Arrays.equals(expected, spiral(matrix));
    }

    private static boolean testVerticalMatrix() {
        int[][] matrix = {{ 1,  2, 3},
                          {12, 13, 4},
                          {11, 14, 5},
                          {10, 15, 6},
                          { 9,  8, 7}};
        int[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9,
                          10, 11, 12, 13, 14, 15};
        return Arrays.equals(expected, spiral(matrix));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNull()) {
            counter++;
            System.out.println("Null matrix test failed!");
        }
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty matrix test failed!");
        }
        if (!testOneElement()) {
            counter++;
            System.out.println("One element test failed!");
        }
        if (!testOneRow()) {
            counter++;
            System.out.println("One row test failed!");
        }
        if (!testTwoRows()) {
            counter++;
            System.out.println("Two rows test failed!");
        }
        if (!testOneColumn()) {
            counter++;
            System.out.println("One column test failed!");
        }
        if (!testTwoColumns()) {
            counter++;
            System.out.println("Two columns test failed!");
        }
        if (!testSquareMatrix()) {
            counter++;
            System.out.println("Square matrix test failed!");
        }
        if (!testHorizontalMatrix()) {
            counter++;
            System.out.println("Horizontal matrix test failed!");
        }
        if (!testVerticalMatrix()) {
            counter++;
            System.out.println("Vertical matrix test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

