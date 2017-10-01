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
        System.out.println(counter + " tests failed.");
    }
}

