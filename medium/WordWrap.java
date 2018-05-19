// Task description: Given an integer array that contains the lengths of words
// in a document and the maximum line length, write a method to arrange the
// words such that the lines are presented neatly on screen. The method should
// ensure there are as few spaces at the end of each line as possible and return
// the total cost calculated as the sum of cubed number of spaces left at each
// line. Please ensure the space between two consecutive words is also accounted
// for.
//
// e.g. For word lengths {3, 2, 2, 5} and line length 6
//      the method should return cost 29 (3^3 + 1 + 1)
//      when arranging words as {{3}, {2, 2}, {5}}
//
// Solution: A simple approach that is actually used in many word processors
// would be to greedily choose how many words to place at each line. The
// runtime complexity of this approach is O(N) and the space complexity O(1)
// but unfortunately it does not return the optimal result. Using the example
// provided above, a greedy algorithm would return placement {{3, 2}, {2}, {5}}
// with a total cost of 0 + 4^3 + 1 = 65 which is worse than the cost of the
// optimal placement {{3}, {2, 2}, {5}}: 2^3 + 1 + 1 = 29.
//
// The first implementation below uses recursion to calculate the optimal cost.
// For each line it attempts to place as many words as possible and at each
// placement it recurses to calculate its overall cost. It keeps track and
// returns the minimum cost. The runtime complexity of this approach is O(W ^ N)
// where W is the average number of words that fit in each line and N is the
// total number of words in the input. The space complexity is O(N) required
// for the recursive stack.

public class WordWrap {

    private static int cube(int num) {
        return num * num * num;
    }

    private static int cost_rec(int[] wordLengths, int index, int lineLength) {

        // All words have been placed.
        if (index >= wordLengths.length) return 0;

        // Attempt to place words in the current line until no more words fit.
        // Return the cost of the best placement, i.e. the minimum cost overall.
        int minCost = Integer.MAX_VALUE;
        int remLength = lineLength;
        for (int i = index; i < wordLengths.length; i++) {

            // Place a space and the next word, break if it does not fit.
            remLength -= (index == i) ? 0 : 1;
            remLength -= wordLengths[i];
            if (remLength < 0) break;

            // Calculate the cost of the placement recursively.
            int cost = cube(remLength) + cost_rec(wordLengths, i + 1, lineLength);
            if (cost < minCost) minCost = cost;
        }
        return minCost;
    }

    private static boolean testOneLine() {
        return cube(3) == cost_rec(new int[] {3, 5, 2, 4}, 0, 20);
    }

    private static boolean testTwoLines() {
        return cube(2) + 1 == cost_rec(new int[] {7, 10, 5, 4, 8}, 0, 20);
    }

    private static boolean testMultiLines() {
        return cube(3) + 1 + 1 == cost_rec(new int[] {3, 2, 2, 5}, 0, 6);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testOneLine()) {
            counter++;
            System.out.println("One line test failed!");
        }
        if (!testTwoLines()) {
            counter++;
            System.out.println("Two lines test failed!");
        }
        if (!testMultiLines()) {
            counter++;
            System.out.println("Multi lines test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

