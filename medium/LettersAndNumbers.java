import static java.lang.Character.isDigit;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a character array that is filled with letters and
// numbers, write a method to find the length of the longest sub-array that
// contains the same number of letters and numbers.
//
// E.g. for input array {'A', '1', 'C', 'D', 'E', '2'} the answer is 2.
//      for input array {'A', 'B', 'C', 'D', 'E'} the answer is 0.
//
// Solution: A brute force solution would be to go through all sub-arrays in
// the given array and find the longest one where the count of numbers and
// letters is equal. The runtime complexity of this approach is O(N), where N
// is the length of the input array.
//
// In the implementation below we calculate the balance of letters vs numbers
// at each position in the input array. A sub-array that has the same number
// of letters and numbers should also have the same balance of numbers vs
// letters at its start and end positions. We use a map to store each balance
// value along with a list of indexes where it was encountered. To find the
// maximum sub-array, we iterate through all balance values and calculate
// the max sub-array length for each, keeping track of the max length overall.
// The runtime and space complexity of this implementation is O(N).

public class LettersAndNumbers {

    private static int find(char[] array) {
        if (array == null || array.length == 0) return 0;
        Map<Integer, List<Integer>> map = new HashMap<>();

        int balance = 0;
        for (int i = 0; i < array.length; i++) {
            balance += (isDigit(array[i]) ? 1 : -1);
            map.computeIfAbsent(balance, (k) -> new ArrayList<>());
            map.get(balance).add(i);
        }

        int max = 0;
        for (List<Integer> list : map.values()) {
            if (list.size() <= 1) continue;
            int temp = list.get(list.size() - 1) - list.get(0);
            if (temp > max) max = temp;
        }
        return max;
    }

    public static boolean testNullArray() {
        return 0 == find(null);
    }

    public static boolean testEmptyArray() {
        return 0 == find(new char[0]);
    }

    public static boolean testNoSubarray() {
        char[] array = new char[] {'A', 'B', 'C', 'D', 'E'};
        return 0 == find(array);
    }

    public static boolean testSubarray() {
        char[] array = new char[] {'A', '1', 'C', 'D', 'E', '2'};
        return 2 == find(array);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNullArray()) {
            counter++;
            System.out.println("Null-array test failed.");
        }
        if (!testEmptyArray()) {
            counter++;
            System.out.println("Empty-array test failed.");
        }
        if (!testNoSubarray()) {
            counter++;
            System.out.println("No sub-array test failed.");
        }
        if (!testSubarray()) {
            counter++;
            System.out.println("Sub-array test failed.");
        }
        System.out.println(counter + " tests failed.");
    }
}

