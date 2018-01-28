import java.util.ArrayList;
import java.util.List;

// Task description: Given a string that consists of unique characters, write a
// method to return a list of all its permutations.
//
// E.g. For input "abc" the answer is {"abc", "bac", "bca", "acb", "cab", "cba"}
//
// Solution: The implementation below first defines how the base cases of empty
// input string or input string that contains only one character should be
// handled. It subsequently removes the first character of the string and calls
// itself recursively, making sure that the permutations of the remainder are
// properly combined with the character that was removed in each step. If n is
// the length of the input string, there are n! permutations in total.
//
// The runtime complexity of combine() is O(n^2), since String.substring() is
// called in total n times and its own complexity is O(n). Method combine() is
// called for each permutation and therefore the total runtime complexity is
// O(n! * n^2).
//
// The second implementation uses a different approach to arrive at the same
// result. It works by splitting the input string in a prefix and a suffix. In
// each recursive call we first check whether the suffix is empty. If that is
// the case, then the prefix contains a permutation that can be added to the
// results. We then iterate through all characters of the suffix, remove the
// current character from the suffix, append it to the prefix and call the
// same method recursively.
//
// The second approach also has runtime complexity of O(n! * n^2) because method
// getPermutations() is called in total n * n! times. It is called n times until
// it reaches the base case to identify a permutation and there are in total n!
// permutations. The runtime complexity of each of those calls is O(n) and thus
// the complexity overall is O(n! * n^2).
//
// Note that both implementations cannot handle input strings that contain
// duplicate characters. In such cases they will produce a list of permutations
// that will contain duplicates. For example, if the input string is "aaa", the
// output will be a list with six elements, all equal to "aaa".

public class UniqueStringPermutations {

    private static List<String> permutations(String input) {
        List<String> results = new ArrayList<>();

        if (input == null || input.isEmpty()) {
            return results;
        }

        if (input.length() == 1) {
            results.add(input);
            return results;
        }

        char c = input.charAt(0);
        String remaining = input.substring(1);
        List<String> permutations = permutations(remaining);
        for (String permutation : permutations) {
            results.addAll(combine(c, permutation));
        }
        return results;
    }

    private static List<String> combine(char c, String input) {
        List<String> results = new ArrayList<>();
        for (int i = 0; i <= input.length(); i++) {
            String start = input.substring(0, i);
            String end = input.substring(i);
            results.add(start + c + end);
        }
        return results;
    }

    private static List<String> permutations2(String input) {
        List<String> results = new ArrayList<>();
        if (input == null || input.isEmpty()) {
            return results;
        }
        getPermutations("", input, results);
        return results;
    }

    private static void getPermutations(String prefix, String suffix,
                                        List<String> results) {

        if (suffix.isEmpty()) {
            results.add(prefix);
            return;
        }

        for (int i = 0; i < suffix.length(); i++) {
            String newSuffix = suffix.substring(0, i) +
                               suffix.substring(i + 1);
            getPermutations(prefix + suffix.charAt(i), newSuffix, results);
        }
    }

    private static boolean testNullString() {
        final List<String> output = permutations(null);
        return output.isEmpty();
    }

    private static boolean testEmptyString() {
        final List<String> output = permutations("");
        return output.isEmpty();
    }

    private static boolean testOneCharacter() {
        final List<String> output = permutations("a");
        return output.size() == 1 &&
               output.contains("a");
    }

    private static boolean testTwoCharacters() {
        final List<String> output = permutations("ab");
        return output.size() == 2 &&
               output.contains("ab") &&
               output.contains("ba");
    }

    private static boolean testThreeCharacters() {
        final List<String> output = permutations("abc");
        return output.size() == 6 &&
               output.contains("abc") &&
               output.contains("bac") &&
               output.contains("bca") &&
               output.contains("acb") &&
               output.contains("cab") &&
               output.contains("cba");
    }

    private static boolean testDuplicates() {
        final List<String> output = permutations("aab");
        return output.size() == 6 &&
               output.contains("aab") &&
               output.contains("aba") &&
               output.contains("baa");
    }

    private static boolean testAllDuplicates() {
        final List<String> output = permutations("aaa");
        return output.size() == 6 &&
               output.contains("aaa");
    }

    private static boolean areEqual(List<String> a, List<String> b) {
        if (a == b) return true;
        if (a.size() != b.size()) return false;
        for (int i = 0; i < a.size(); i++) {
            if (!b.contains(a.get(i))) return false;
        }
        return true;
    }

    private static boolean testPermutations2() {
        return areEqual(permutations(null), permutations2(null)) &&
               areEqual(permutations(""), permutations2("")) &&
               areEqual(permutations("a"), permutations2("a")) &&
               areEqual(permutations("ab"), permutations2("ab")) &&
               areEqual(permutations("abc"), permutations2("abc")) &&
               areEqual(permutations("aab"), permutations2("aab")) &&
               areEqual(permutations("aaa"), permutations2("aaa"));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNullString()) {
            System.out.println("Null string test failed!");
            counter++;
        }
        if (!testEmptyString()) {
            System.out.println("Empty string test failed!");
            counter++;
        }
        if (!testOneCharacter()) {
            System.out.println("One character string test failed!");
            counter++;
        }
        if (!testTwoCharacters()) {
            System.out.println("Two characters string test failed!");
            counter++;
        }
        if (!testThreeCharacters()) {
            System.out.println("Three characters string test failed!");
            counter++;
        }
        if (!testDuplicates()) {
            System.out.println("Duplicate characters test failed!");
            counter++;
        }
        if (!testAllDuplicates()) {
            System.out.println("All duplicate characters test failed!");
            counter++;
        }
        if (!testPermutations2()) {
            System.out.println("Permutations 2 test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

