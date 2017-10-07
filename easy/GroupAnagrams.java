import java.util.Arrays;
import java.util.Comparator;

// Task description: Given an array of Strings, write a method to sort the
// array so that all the anagrams are next to each other.
//
// E.g. For input array {"care", "how", "acre", "who", "leg"}
//        the output is {"acre", "care", "how", "who", "leg"}

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

    private static boolean testSort_NoAnagrams() {
        String[] input = {"dad", "acre", "how", "leg"};
        sort(input);

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

    public static void main(String[] args) {
        int counter = 0;
        if (!testSort_NoAnagrams()) {
            System.out.println("Sort test without anagrams failed!");
            counter++;
        }
        if (!testSort()) {
            System.out.println("Sort test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

