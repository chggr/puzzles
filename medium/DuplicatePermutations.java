import java.util.ArrayList;
import java.util.List;

// Task description: Given a string that might contain duplicate characters,
// write a method that returns all its unique permutations.
//
// E.g. for input String "abc"
//      the method should return ["abc", "acb", "bac", "bca", "cab", "cba"]
//
//      for input String "aaaaa"
//      the method should return ["aaaaa"]
//
// Solution: This task is similar to the UniquePermutations.java puzzle. Indeed
// we could follow the same approach and store the results in a Set to eliminate
// any duplicates. This approach though would not be efficient if the input
// string contains many duplicate characters, e.g. "aaaaaaaa". In that case we
// would have to go through n! permutations although there is clearly only one
// unique permutation.
//
// The implementation below builds a frequency table that contains the frequency
// of each letter in the input string. It then recursively scans the table and
// sets each character for every permutation. This algorithm is much faster and
// more efficient than the one discussed previously.

public class DuplicatePermutations {

    private static int[] buildFrequencyTable(String s) {
        int[] frequencies = new int[128];
        for (char c : s.toCharArray()) {
            frequencies[c - 'a']++;
        }
        return frequencies;
    }

    private static void setCharAt(char[] array, int pos, int[] freq,
                                  List<String> results) {

        if (pos == array.length) {
            results.add(new String(array));
            return;
        }

        for (int j = 0; j < freq.length; j++) {
            if (freq[j] > 0) {
                freq[j]--;
                array[pos] = (char) ('a' + j);
                setCharAt(array, pos + 1, freq, results);
                freq[j]++;
            }
        }
    }

    private static List<String> permutations(String s) {
        List<String> results = new ArrayList<>();
        if (s == null || s.isEmpty()) {
            return results;
        }

        char[] array = new char[s.length()];
        int[] freq = buildFrequencyTable(s);
        setCharAt(array, 0, freq, results);
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

    private static boolean testDuplicates() {
        final List<String> output = permutations("aabb");
        return output.size() == 6 &&
               output.contains("aabb") &&
               output.contains("abab") &&
               output.contains("abba") &&
               output.contains("baab") &&
               output.contains("baba") &&
               output.contains("bbaa");
    }

    private static boolean testAllDuplicates() {
        final List<String> output = permutations("aaaaa");
        return output.size() == 1 &&
               output.contains("aaaaa");
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
        System.out.println(counter + " tests failed.");
    }
}

