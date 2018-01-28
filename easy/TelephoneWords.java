import static java.util.Arrays.asList;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Create a method to return all possible words that can be
// compiled based on an individual's telephone number and using the number to
// character definition found in most modern telephone keyboards.
//
// Digit     Characters            E.g. For telephone number 43556
// 0         0                          one possible word is HELLO
// 1         1
// 2         A / B / C
// 3         D / E / F
// 4         G / H / I
// 5         J / K / L
// 6         M / N / O
// 7         P / R / S
// 8         T / U / V
// 9         W / X / Y
//
// Solution: The number of words that correspond to a given telephone number
// with n digits will be 3^n, since each digit can be represented using one out
// of three possible characters. The first implementation below iteratively goes
// through all digits in the telephone number and expands the list of words
// accordingly. The second implementation works in a similar way but is
// recursive. The runtime complexity of both approaches is O(3^n).
//
// No assumption is made with regards to the number of digits the telephone
// number has. If this was fixed and known in advance, we could have avoided
// allocating memory unnecessarily. In that case we could simply define a fixed
// character array and each iteration would change the letter at its
// corresponding position.

public class TelephoneWords {

    private static final Map<Integer, List<Character>> TEL;

    static {
        TEL = new HashMap<>();
        TEL.put(0, asList('0'));
        TEL.put(1, asList('1'));
        TEL.put(2, asList('A', 'B', 'C'));
        TEL.put(3, asList('D', 'E', 'F'));
        TEL.put(4, asList('G', 'H', 'I'));
        TEL.put(5, asList('J', 'K', 'L'));
        TEL.put(6, asList('M', 'N', 'O'));
        TEL.put(7, asList('P', 'R', 'S'));
        TEL.put(8, asList('T', 'U', 'V'));
        TEL.put(9, asList('W', 'X', 'Y'));
    }

    private static List<String> getWordsIteratively(int number) {

        // Process rightmost digit of the number.
        List<String> results = new ArrayList<>();
        for (Character c : TEL.get(number % 10)) {
            results.add(c.toString());
        }
        number /= 10;

        // Process remaining digits from right to left.
        while (number != 0) {
            List<String> newResults = new ArrayList<>();
            for (Character c : TEL.get(number % 10)) {
                for (String r : results) {
                    newResults.add(c + r);
                }
            }
            results = newResults;
            number /= 10;
        }
        return results;
    }

    private static List<String> getWordsRecursively(int number) {
        List<String> results = new ArrayList<>();
        for (Character c : TEL.get(number % 10)) {
            results.add(c.toString());
        }

        return processNextDigit(number / 10, results);
    }

    private static List<String> processNextDigit(int number, List<String> words) {
        if (number == 0) {
            return words;
        }

        List<String> newWords = new ArrayList<>();
        for (Character c : TEL.get(number % 10)) {
            for (String w : words) {
                newWords.add(c + w);
            }
        }
        return processNextDigit(number / 10, newWords);
    }

    private static boolean testGetWordsIteratively() {
        return asList("0").equals(getWordsIteratively(0)) &&
               asList("1").equals(getWordsIteratively(1)) &&
               asList("10").equals(getWordsIteratively(10)) &&
               asList("AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF")
                   .equals(getWordsIteratively(23));
    }

    private static boolean testGetWordsRecursively() {
        return asList("0").equals(getWordsRecursively(0)) &&
               asList("1").equals(getWordsRecursively(1)) &&
               asList("10").equals(getWordsRecursively(10)) &&
               asList("AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF")
                   .equals(getWordsRecursively(23));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testGetWordsIteratively()) {
            System.out.println("Test get words iteratively failed!");
            counter++;
        }
        if (!testGetWordsRecursively()) {
            System.out.println("Test get words recursively failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

