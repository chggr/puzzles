// Task description: Given two strings, write a method to return the minimum
// number of operations required to transform one string to the other. The
// operations allowed are: delete, insert or change a character.
//
// E.g. for input strings "CAT" and "BUT" the method should return 2.
//      for input strings "CAT" and "CAT" the method should return 0.
//
// Solution: The first implementation below uses a recursive approach to
// calculate the minimum number of operations required to transform one string
// to the other. It checks whether the characters at each position match. If
// yes, then it moves both fromPos and toPos pointers to the next character.
// If no, it calls itself recursively to determine which of the operations
// (delete, insert, update) will yield the minimum number of changes. The
// runtime complexity of this algorithm is O(3^N) because in the worst case the
// method is called recursively three times. The space complexity is O(N), where
// N is the length of the shortest input string. This is required for the
// recursive stack.
//
// The aforementioned approach is pretty wasteful as there are many overlapping
// problems that are calculated multiple times. The second implementation uses
// dynamic programming to compute the minimum number of operations from the
// bottom up. A memo table is used to memorize previously computed results and
// is filled from the bottom up. Both the runtime and space complexities of
// this approach are O(M*N) where M and N are the lengths of the input strings.

public class EditDistance {

    private static int min(int a, int b, int c) {
        return a < b ? (a < c ? a : c) : b < c ? b : c;
    }

    private static int distance_rec(String from, int fromPos,
                                    String to, int toPos) {

        if (fromPos >= from.length()) return to.length() - toPos;
        if (toPos >= to.length()) return from.length() - fromPos;

        // Match
        if (from.charAt(fromPos) == to.charAt(toPos)) {
            return distance_rec(from, fromPos + 1, to, toPos + 1);
        }

        // Mismatch
        int delete = distance_rec(from, fromPos + 1, to, toPos);
        int insert = distance_rec(from, fromPos, to, toPos + 1);
        int update = distance_rec(from, fromPos + 1, to, toPos + 1);

        return 1 + min(delete, insert, update);
    }

    private static int distance_dyn(String from, String to) {
        int[][] memo = new int[from.length() + 1][to.length() + 1];

        for (int f = 0; f <= from.length(); f++) {
            for (int t = 0; t <= to.length(); t++) {

                // From is empty
                if (f == 0) {
                    memo[f][t] = t;
                    continue;
                }

                // To is empty
                if (t == 0) {
                    memo[f][t] = f;
                    continue;
                }

                // Match
                if (from.charAt(f - 1) == to.charAt(t - 1)) {
                    memo[f][t] = memo[f - 1][t - 1];
                    continue;
                }

                // Mismatch
                int delete = memo[f][t - 1];
                int insert = memo[f - 1][t];
                int update = memo[f - 1][t - 1];

                memo[f][t] = 1 + min(insert, delete, update);
            }
        }

        return memo[from.length()][to.length()];
    }

    private static boolean testEmpty() {
        return 3 == distance_rec("CAT", 0, "", 0) &&
               3 == distance_rec("", 0, "CAT", 0) &&
               3 == distance_dyn("CAT", "") &&
               3 == distance_dyn("", "CAT");
    }

    private static boolean testSame() {
        return 0 == distance_rec("CAT", 0, "CAT", 0) &&
               0 == distance_dyn("CAT", "CAT");
    }

    private static boolean testOneEdit() {
        return 1 == distance_rec("CAT", 0, "CAST", 0) &&
               1 == distance_rec("CAT", 0, "CT", 0) &&
               1 == distance_rec("CAT", 0, "CUT", 0) &&
               1 == distance_dyn("CAT", "CAST") &&
               1 == distance_dyn("CAT", "CT") &&
               1 == distance_dyn("CAT", "CUT");
    }

    private static boolean testTwoEdits() {
        return 2 == distance_rec("CAT", 0, "CASTS", 0) &&
               2 == distance_rec("CAT", 0, "C", 0) &&
               2 == distance_rec("CAT", 0, "BUT", 0) &&
               2 == distance_dyn("CAT", "CASTS") &&
               2 == distance_dyn("CAT", "C") &&
               2 == distance_dyn("CAT", "BUT");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty string test failed!");
        }
        if (!testSame()) {
            counter++;
            System.out.println("Same string test failed!");
        }
        if (!testOneEdit()) {
            counter++;
            System.out.println("One edit string test failed!");
        }
        if (!testTwoEdits()) {
            counter++;
            System.out.println("Two edits string test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

