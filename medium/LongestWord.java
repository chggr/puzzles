import java.util.Arrays;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

// Task description: Write a method to return the longest word in a dictionary
// that is made up from two or more other words in it.
//
// E.g. for dictionary {"a", "we", "some", "awesome", "mass", "amass"}
//      the method should return: "awesome"
//
// Solution: The implementation below is using a recursive approach with
// memoization to identify the longest word in the dictionary that is made up
// from other words in it. It first populates the "memo" map with all words in
// the dictionary and then goes through each word in order from longest to
// shortest, checking whether each one satisfies the criteria and can be
// returned. Memoization allows us to cache and reuse previous results and thus
// speed up execution. Additionally, we use flag "isOriginal" to ensure that
// method canBuild() will not return true when it finds the original word in the
// dictionary, but will attempt to break it up. The runtime complexity of method
// canBuild() is O(N^2), where N is the average number of letters in a word.
// If there is a total of D words in the dictionary, the overall runtime
// complexity is O(D * N^2).

public class LongestWord {

    private static boolean canBuild(String word,
                                    Map<String, Boolean> memo,
                                    boolean isOriginal) {

        if (!isOriginal && memo.containsKey(word)) {
            return memo.get(word);
        }

        for (int i = 1; i < word.length(); i++) {
            String prefix = word.substring(0, i);
            if (!memo.containsKey(prefix) ||
                memo.get(prefix) == false) continue;

            String suffix = word.substring(i);
            if (canBuild(suffix, memo, false)) {
                memo.put(word, true);
                return true;
            }
        }

        memo.put(word, false);
        return false;
    }

    private static String longest(String[] dict) {
        Map<String, Boolean> memo = new HashMap<>();
        for (String word : dict) memo.put(word, true);

        // Sort by word length descending.
        Arrays.sort(dict, (a, b) -> b.length() - a.length());
        for (String word : dict) {
            if (canBuild(word, memo, true)) return word;
        }
        return null;
    }

    private static boolean testNoLongestWord() {
        return null == longest(new String[] {"a", "we", "mass"});
    }

    private static boolean testLongestWord() {
        return "awesome".equals(longest(
                    new String[] {"a", "we", "some", "awesome", "mass", "amass"}));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNoLongestWord()) {
            counter++;
            System.out.println("No word test failed!");
        }
        if (!testLongestWord()) {
            counter++;
            System.out.println("Longest word test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

