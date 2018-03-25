import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

// Task description: Given a dictionary of words and a sentence where all spaces
// have been removed, write a method to return the minimum number of unmatched
// characters when the spaces have been reintroduced to the sentence.
//
// E.g. for dictionary {"this", "is", "my", "favourite", "food"}
//      if input is: "thisismyfavouritefood" the method should return 0
//      if input is: "thisisherfavouritefood" the method should return 3;
//
// Solution: The first implementation below is a brute force recursive approach.
// Method respace_rec() finds the best possible position where the first space
// should be added by calculating all possible prefixes and calling itself
// recursively for each suffix. The runtime complexity of this approach depends
// on the language of the sentence, but in the worst case it is O(2^n) where n
// is the sentence length. That is because for each character we need to explore
// two possible options: insert a space after it or not. Please note that two
// optimizations have been applied to improve this runtime: (1) if the number of
// current missing characters exceeds the minimum found so far, then this
// recursive path is not taken and (2) if there is a path with zero missing
// characters, we immediately return from recursion as there is no other better
// possible path.
//
// The second implementation is similar to the first one but memoization is used
// to significantly improve the runtime complexity. At each position we compute
// the best possible re-spacing only once and store the minimum missing
// characters in a memo[] array. This allows us to reuse previously calculated
// results and therefore the runtime complexity has now dropped to just O(n^2).
// We now only do 1 + 2 + 3 + ... + n calls in total, which is n * (n + 1) / 2
// and thus the runtime complexity is O(n^2).
//
// Finally the third implementation uses an iterative, bottom-up, dynamic
// programming approach to calculate the minimum missing characters. It starts
// from the end of the sentence and at each position stores the minimum number
// of missing characters for the string starting at that position into a memo
// array. To compute the result at each position we use the calculations already
// performed in all subsequent positions. The runtime complexity of this
// approach is also O(n^2).

public class Respace {

    private static final Set<String> DICT = new HashSet<>(
            Arrays.asList("this", "is", "my", "favourite", "food"));

    private static int respace_rec(Set<String> dict, String s) {
        if (s == null || s.isEmpty()) return 0;

        int min = Integer.MAX_VALUE;
        for (int i = 0; i < s.length(); i++) {
            String prefix = s.substring(0, i + 1);
            int missing = dict.contains(prefix) ? 0 : prefix.length();
            if (missing >= min) continue;

            missing += respace_rec(dict, s.substring(i + 1));
            if (missing == 0) return 0;
            if (missing < min) min = missing;
        }
        return min;
    }

    private static int respace_memo(Set<String> dict, String s, int idx, int[] memo) {
        if (idx >= s.length()) return 0;
        if (memo[idx] != -1) return memo[idx];

        int min = Integer.MAX_VALUE;
        for (int i = idx; i < s.length(); i++) {
            String prefix = s.substring(idx, i + 1);
            int missing = dict.contains(prefix) ? 0 : prefix.length();
            if (missing >= min) continue;

            missing += respace_memo(dict, s, i + 1, memo);
            if (missing < min) min = missing;
            if (missing == 0) break;
        }
        memo[idx] = min;
        return min;
    }

    private static int respace_memo(Set<String> dict, String s) {
        if (s == null || s.isEmpty()) return 0;

        int[] memo = new int[s.length()];
        Arrays.fill(memo, -1);
        return respace_memo(dict, s, 0, memo);
    }

    private static int respace_dyn(Set<String> dict, String s) {
        if (s == null || s.isEmpty()) return 0;

        int[] memo = new int[s.length()];
        for (int i = s.length() - 1; i >= 0; i--) {
            int min = Integer.MAX_VALUE;
            for (int j = i + 1; j <= s.length(); j++) {
                String prefix = s.substring(i, j);
                int missing = dict.contains(prefix) ? 0 : prefix.length();
                if (missing >= min) continue;

                if (j < memo.length) missing += memo[j];
                if (missing < min) min = missing;
                if (missing == 0) break;
            }
            memo[i] = min;
        }
        return memo[0];
    }

    private static boolean testNullWord() {
        return 0 == respace_rec(DICT, null) &&
               0 == respace_memo(DICT, null) &&
               0 == respace_dyn(DICT, null);
    }

    private static boolean testEmptyWord() {
        return 0 == respace_rec(DICT, "") &&
               0 == respace_memo(DICT, "") &&
               0 == respace_dyn(DICT, "");
    }

    private static boolean testSingleWord() {
        String s = "this";
        return 0 == respace_rec(DICT, s) &&
               0 == respace_memo(DICT, s) &&
               0 == respace_dyn(DICT, s);
    }

    private static boolean testSingleWord_WithUnknowns() {
        String s = "thistest";
        return 4 == respace_rec(DICT, s) &&
               4 == respace_memo(DICT, s) &&
               4 == respace_dyn(DICT, s);
    }

    private static boolean testManyWords() {
        String s = "thisismyfavouritefood";
        return 0 == respace_rec(DICT, s) &&
               0 == respace_memo(DICT, s) &&
               0 == respace_dyn(DICT, s);
    }

    private static boolean testManyWords_WithUnknowns() {
        String s = "thisisherfavouritefood";
        return 3 == respace_rec(DICT, s) &&
               3 == respace_memo(DICT, s) &&
               3 == respace_dyn(DICT, s);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNullWord()) {
            counter++;
            System.out.println("Null word test failed!");
        }
        if (!testEmptyWord()) {
            counter++;
            System.out.println("Empty word test failed!");
        }
        if (!testSingleWord()) {
            counter++;
            System.out.println("Single word test failed!");
        }
        if (!testSingleWord_WithUnknowns()) {
            counter++;
            System.out.println("Single word with unknowns test failed!");
        }
        if (!testManyWords()) {
            counter++;
            System.out.println("Many words test failed!");
        }
        if (!testManyWords_WithUnknowns()) {
            counter++;
            System.out.println("Many words with unknowns test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

