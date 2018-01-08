import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given an array of integers, design an algorithm to find
// all pairs of whose sum is equal to a specified value.
//
// E.g. for array {-4, 0, 8, 5, 1} and target value 7
//      it should return an empty list
//
//      for array {-4, 0, 8, 5, 1} and target value 1
//      it should return [(-4, 5), (0, 1)]
//
// Solution: The first implementation below uses a brute force algorithm to
// iterate through all elements in the array twice and identify pairs with the
// given sum. The runtime complexity of this approach is O(N^2) where N is the
// length of the array. The space complexity is O(1), as no extra space is
// required.
//
// The second implementation is using a map to keep track of all values and how
// many times each has been seen. The algorithm iterates through the array only
// once and for each element calculates its complement, i.e. the number required
// to reach the given sum. If the complement has already been seen, then the two
// values are paired. If the complement has not yet been seen, then the current
// element is simply added to the map. The runtime complexity of this approach
// is O(N) because we iterate through the array only once. The space complexity
// is also O(N), since we are using extra space for the map.
//
// Finally the third implementation sorts the input array and then finds the
// pairs in a single pass. It keeps track of the head and tail of the array and
// moves both of them in sequence towards the center of the array, finding
// eligible pairs in the process. The runtime complexity of this approach is
// O(N*logN) to sort the array and O(N) to find the pairs. The space complexity
// is O(1) as no extra space is required.

public class PairsWithSum {

    public static final class Pair<T> {
        private final T one;
        private final T two;

        public Pair(T one, T two) {
            this.one = one;
            this.two = two;
        }

        public T getOne() {
            return one;
        }

        public T getTwo() {
            return two;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair<?>)) return false;

            final Pair<?> other = (Pair<?>) o;
            return other.one.equals(one) &&
                   other.two.equals(two);
        }

        @Override
        public int hashCode() {
            int code = 17;
            code = 31 * code + one.hashCode();
            code = 31 * code + two.hashCode();
            return code;
        }

        @Override
        public String toString() {
            return "(" + one + ", " + two + ")";
        }
    }

    private static List<Pair<Integer>> findBrute(int[] array, int sum) {
        List<Pair<Integer>> results = new ArrayList<>();
        for (int i = 0; i < array.length; i++) {
            for (int j = i + 1; j < array.length; j++) {
                if (array[i] + array[j] == sum) {
                    results.add(new Pair<> (array[i], array[j]));
                }
            }
        }
        return results;
    }

    private static List<Pair<Integer>> findMap(int[] array, int sum) {
        List<Pair<Integer>> results = new ArrayList<>();
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < array.length; i++) {
            int comp = sum - array[i];
            Integer compCount = map.get(comp);
            if (compCount == null || compCount == 0) {
                Integer count = map.get(array[i]);
                map.put(array[i], count == null ? 1 : count + 1);
            } else {
                map.put(comp, compCount - 1);
                results.add(new Pair<>(comp, array[i]));
            }
        }
        return results;
    }

    private static List<Pair<Integer>> findSort(int[] array, int sum) {
        List<Pair<Integer>> results = new ArrayList<>();
        Arrays.sort(array);
        int end = array.length - 1;
        for (int start = 0; start < end; start++) {
            while (array[start] + array[end] > sum) {
                end--;
            }
            if (array[start] + array[end] == sum) {
                results.add(new Pair<>(array[start], array[end]));
            }
        }
        return results;
    }

    private static boolean testEmptyArray() {
        int[] array = {};
        return findBrute(array, 10).isEmpty() &&
               findMap(array, 10).isEmpty() &&
               findSort(array, 10).isEmpty();
    }

    private static boolean testNoResult() {
        int[] array = {-4, 0, 8, 5, 1};
        return findBrute(array, 7).isEmpty() &&
               findMap(array, 7).isEmpty() &&
               findSort(array, 7).isEmpty();
    }

    private static boolean testManyResults() {
        int[] array = {-4, 0, 8, 5, 1};
        List<Pair<Integer>> expected = Arrays.asList(
                new Pair<>(-4, 5), new Pair<>(0, 1));
        return findBrute(array, 1).equals(expected) &&
               findMap(array, 1).equals(expected) &&
               findSort(array, 1).equals(expected);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmptyArray()) {
            System.out.println("Empty array test failed!");
            counter++;
        }
        if (!testNoResult()) {
            System.out.println("No result test failed!");
            counter++;
        }
        if (!testManyResults()) {
            System.out.println("Many results test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

