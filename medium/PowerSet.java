import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

// Task description: Write a method to return all subsets of a set.
//
// E.g. For set {1, 2, 3} the method should return:
//      {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}
//
// Solution: When generating a subset of a given set, each element can either
// be or not be in the subset. Therefore the total number of subsets will
// always be 2^n, where n is the size of the original set. The implementation
// below is recursive and works as follows: The base case is when the input
// set is empty. The output in this case will be a set containing just an empty
// set. If the input set is not empty, we iterate through all its elements and
// for each one we calculate the subsets of the remaining elements. These are
// added to the final result, along with additional subsets that contain the
// element of the iteration.
//
// The second implementation below uses an iterative approach to arrive to the
// same result. All subsets can be represented as a binary number where each
// position corresponds to whether the given element in the original set will be
// part of the subset or not. What we then need to do is iterate from 0 to 2^n
// and generate each subset accordingly.

public class PowerSet {

    private static Set<Set<Integer>> getSubsets (Set<Integer> set) {
        Set<Set<Integer>> result = new HashSet<>();

        if (set.isEmpty()) {
            result.add(new HashSet<>());
            return result;
        }

        for (Integer i : set) {
            Set<Integer> remaining = new HashSet<>(set);
            remaining.remove(i);

            final Set<Set<Integer>> subsets = getSubsets(remaining);
            result.addAll(subsets);

            for (Set<Integer> subset: subsets) {
                Set<Integer> newSubset = new HashSet<>(subset);
                newSubset.add(i);
                result.add(newSubset);
            }
        }
        return result;
    }

    private static List<List<Integer>> getSublists (List<Integer> list) {
        final List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < Math.pow(2, list.size()); i++) {
            result.add(getList(list, i));
        }
        return result;
    }

    private static List<Integer> getList(List<Integer> input, int value) {
        final List<Integer> result = new ArrayList<>();
        for (int i = 0; i < input.size(); i++) {
            if ((value & (1 << i)) > 0) {
                result.add(input.get(i));
            }
        }
        return result;
    }

    private static boolean testGetSubsets_Empty() {
        Set<Integer> input = new HashSet<>();
        Set<Set<Integer>> output = getSubsets(input);

        return 1 == output.size() &&
               output.contains(new HashSet<>());
    }

    private static boolean testGetSublists_Empty() {
        List<Integer> input = new ArrayList<>();
        List<List<Integer>> output = getSublists(input);

        return 1 == output.size() &&
               output.contains(new ArrayList());
    }

    private static boolean testGetSubsets_OneElement() {
        Set<Integer> input = new HashSet<>(Arrays.asList(1));
        Set<Set<Integer>> output = getSubsets(input);

        return 2 == output.size() &&
               output.contains(new HashSet<>()) &&
               output.contains(new HashSet<>(Arrays.asList(1)));
    }

    private static boolean testGetSublists_OneElement() {
        List<Integer> input = Arrays.asList(1);
        List<List<Integer>> output = getSublists(input);

        return 2 == output.size() &&
               output.contains(new ArrayList<>()) &&
               output.contains(Arrays.asList(1));
    }

    private static boolean testGetSubsets_ManyElements() {
        Set<Integer> input = new HashSet<>(Arrays.asList(1, 2, 3, 4));
        Set<Set<Integer>> output = getSubsets(input);

        return 16 == output.size() &&
               output.contains(new HashSet<>()) &&
               output.contains(new HashSet<>(Arrays.asList(1))) &&
               output.contains(new HashSet<>(Arrays.asList(2))) &&
               output.contains(new HashSet<>(Arrays.asList(3))) &&
               output.contains(new HashSet<>(Arrays.asList(4))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 2))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 3))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(2, 3))) &&
               output.contains(new HashSet<>(Arrays.asList(2, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(3, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 2, 3))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 2, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 3, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(2, 3, 4))) &&
               output.contains(new HashSet<>(Arrays.asList(1, 2, 3, 4)));
    }

    private static boolean testGetSublists_ManyElements() {
        List<Integer> input = Arrays.asList(1, 2, 3, 4);
        List<List<Integer>> output = getSublists(input);

        return 16 == output.size() &&
               output.contains(new ArrayList<>()) &&
               output.contains(Arrays.asList(1)) &&
               output.contains(Arrays.asList(2)) &&
               output.contains(Arrays.asList(3)) &&
               output.contains(Arrays.asList(4)) &&
               output.contains(Arrays.asList(1, 2)) &&
               output.contains(Arrays.asList(1, 3)) &&
               output.contains(Arrays.asList(1, 4)) &&
               output.contains(Arrays.asList(2, 3)) &&
               output.contains(Arrays.asList(2, 4)) &&
               output.contains(Arrays.asList(3, 4)) &&
               output.contains(Arrays.asList(1, 2, 3)) &&
               output.contains(Arrays.asList(1, 2, 4)) &&
               output.contains(Arrays.asList(1, 3, 4)) &&
               output.contains(Arrays.asList(2, 3, 4)) &&
               output.contains(Arrays.asList(1, 2, 3, 4));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testGetSubsets_Empty()) {
            System.out.println("Get subsets empty input test failed!");
            counter++;
        }
        if (!testGetSublists_Empty()) {
            System.out.println("Get sublists empty input test failed!");
            counter++;
        }
        if (!testGetSubsets_OneElement()) {
            System.out.println("Get subsets one element input test failed!");
            counter++;
        }
        if (!testGetSublists_OneElement()) {
            System.out.println("Get sublists one element input test failed!");
            counter++;
        }
        if (!testGetSubsets_ManyElements()) {
            System.out.println("Get subsets many elements input test failed!");
            counter++;
        }
        if (!testGetSublists_ManyElements()) {
            System.out.println("Get sublists many elements input test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

