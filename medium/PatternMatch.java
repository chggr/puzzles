// Task description: Two strings are provided, the pattern and the value. The
// pattern consists of just the letters 'a' and 'b' and describes a possible
// string pattern. Write a method to return whether the given pattern applies
// to the provided value.
//
// E.g. For value "catDog" patterns "a", "b", "ba", "ab" match.
//                         patterns "aba", "bab", "aa, "bb" do not match.
//
// Solution: The implementation below is using two helper methods to achieve
// the desired result. The first method counts occurrences of a given character
// within a string and the second method applies the provided pattern onto the
// input string and returns the string representation of the given character.
//
// In the main method, we first need to count how many 'a' and 'b' our pattern
// contains. We subsequently iterate through all possible lengths for 'a' and
// 'b', smartly skipping all combinations that do not result in the correct
// length for our input string. The values of 'a' and 'b' are then extracted via
// a helper method and we return true if a match has been found. If no match is
// identified for all possible values of 'a' and 'b', then the method returns
// false.
//
// The runtime complexity of this algorithm is O(n^3), but practically it is
// much lower since most combinations for aLength and bLength are skipped
// because they do not lead to the correct input string length.

public class PatternMatch {

    private static boolean isMatch(final String pattern, final String input) {
        if (pattern.length() == 0) return input.length() == 0;

        int aCount = count(pattern, 'a');
        int bCount = count(pattern, 'b');

        for (int aLength = 1; aLength <= input.length(); aLength++) {
            for (int bLength = 1; bLength <= input.length(); bLength++) {
                if (aCount * aLength + bCount * bLength != input.length()) {
                    continue;
                }

                String a = get('a', pattern, input, aLength, bLength);
                String b = get('b', pattern, input, bLength, aLength);
                if (input.equals(pattern.replace("a", a).replace("b", b))) {
                    return true;
                }
            }
        }
        return false;
    }

    // Counts occurrences of a character within a string.
    private static int count(final String s, final char c) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == c) count++;
        }
        return count;
    }

    // Returns the string representation of the given character c by applying
    // the provided pattern onto the input string.
    private static String get(final char c,
                              final String pattern,
                              final String input,
                              final int myLength,
                              final int otherLength) {
        int index = pattern.indexOf(c) * otherLength;
        return index < 0 ? "" : input.substring(index, index + myLength);
    }

    private static boolean testEmptyStrings() {
        return isMatch("", "") &&
               !isMatch("a", "") &&
               !isMatch("b", "") &&
               !isMatch("", "cat");
    }

    private static boolean testMatch() {
        return isMatch("a", "catdog") &&
               isMatch("b", "catdog") &&
               isMatch("ab", "catdog") &&
               isMatch("ba", "catdog");
    }

    private static boolean testNotMatch() {
        return !isMatch("aa", "catdog") &&
               !isMatch("bb", "catdog") &&
               !isMatch("aba", "catdog") &&
               !isMatch("bab", "catdog");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmptyStrings()) {
            System.out.println("Empty strings test failed!");
            counter++;
        }
        if (!testMatch()) {
            System.out.println("Match test failed!");
            counter++;
        }
        if (!testNotMatch()) {
            System.out.println("Not match test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

