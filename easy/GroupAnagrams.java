import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

// Task description: Given an array of Strings, write a method to sort the
// array so that all the anagrams are next to each other.
//
// E.g. For input array {"care", "how", "acre", "who", "leg"}
//        the output is {"acre", "care", "how", "who", "leg"}
//
// Solution: There are two ways to determine whether two strings are anagrams:
// (1) by counting the occurrences of each distinct character in each word and
// return true if they match or (2) by sorting both strings and comparing them.
//
// Both implementations below use the second approach. The first implementation
// defines a Comparator that sorts two strings and then compares them. This
// Comparator can be used in the standard Arrays.sort() method to sort the input
// array so that all anagrams are next to each other. The number of comparisons
// required in quicksort is 2 * n * logn where n is the number of elements to be
// sorted. Therefore the overall runtime complexity is O(n * logn * k * logk),
// where n is the number of words in the input array and k is the average length
// of each word. The space complexity is O(1).
//
// The first approach can be improved by using a variation of bucket sort. We
// first create a TreeMap that maps the sorted version of each word to a list of
// its anagrams. We then iterate through all lists and put the elements back in
// the input array in sorted order. The runtime complexity has now been improved
// to O(n * k * logk) because we just need to sort each word once and this takes
// O(k * logk). The space complexity is O(n) for the map.

public class GroupAnagrams {

    private static String sortChars(String input) {
        char[] chars = input.toCharArray();
        Arrays.sort(chars);
        return String.valueOf(chars);
    }

    private static void sort(String[] input) {
        Arrays.sort(input, new Comparator<String>() {

            @Override
            public int compare(String a, String b) {
                return sortChars(a).compareTo(sortChars(b));
            }
        });
    }

    private static void sortBucket(String[] input) {
        Map<String, List<String>> map = new TreeMap<>();
        for (String s : input) {
            String key = sortChars(s);
            map.computeIfAbsent(key, (k) -> new ArrayList<>());
            map.get(key).add(s);
        }

        int idx = 0;
        for (List<String> list : map.values()) {
            for (String s : list) {
                input[idx++] = s;
            }
        }
    }

    private static boolean testSort_NoAnagrams() {
        String[] input = {"dad", "acre", "how", "leg"};
        sort(input);

        return "acre" == input[0] && "dad" == input[1] &&
               "leg" == input[2] && "how" == input[3];
    }

    private static boolean testSortBucket_NoAnagrams() {
        String[] input = {"dad", "acre", "how", "leg"};
        sortBucket(input);

        return "acre" == input[0] && "dad" == input[1] &&
               "leg" == input[2] && "how" == input[3];
    }

    private static boolean testSort() {
        String[] input = {"care", "how", "acre", "who", "race", "dad"};
        sort(input);

        return "care" == input[0] && "acre" == input[1] &&
               "race" == input[2] && "dad" == input[3] &&
               "how" == input[4] && "who" == input[5];
    }

    private static boolean testSortBucket() {
        String[] input = {"care", "how", "acre", "who", "race", "dad"};
        sortBucket(input);

        return "care" == input[0] && "acre" == input[1] &&
               "race" == input[2] && "dad" == input[3] &&
               "how" == input[4] && "who" == input[5];
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testSort_NoAnagrams()) {
            System.out.println("Sort test without anagrams failed!");
            counter++;
        }
        if (!testSortBucket_NoAnagrams()) {
            System.out.println("Bucket sort test without anagrams failed!");
            counter++;
        }
        if (!testSort()) {
            System.out.println("Sort test failed!");
            counter++;
        }
        if (!testSortBucket()) {
            System.out.println("Bucket sort test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

