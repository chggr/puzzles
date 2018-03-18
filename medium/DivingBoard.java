import java.util.HashSet;
import java.util.Set;

// Task description: You are building a diving board by placing K pieces of wood
// end-to-end. There are two types of planks, one of length SHORT and another of
// length LONG. Write a method to generate all possible lengths for the diving
// board.
//
// Solution: The first implementation below is a backtracking recursive solution
// where at each step we use either the SHORT or the LONG plank. Once we have
// put k planks, the diving board is ready and its length is added to the set
// of possible lengths. The runtime complexity of this approach is O(2 ^ k)
// because the method calls itself twice at each recursion. The space complexity
// is O(k) because the depth of the execution stack grows up to k frames.
//
// The second implementation is iterative and is based on the observation that
// we do not need to go through all arrangements of planks. We just need to go
// through all unique sets of K planks. Therefore we first construct our base
// case where all planks are SHORT and iteratively remove a SHORT plank, add a
// LONG plank and save the new length. The runtime complexity of this approach
// is just O(k) and the space complexity is O(1).

public class DivingBoard {

    // Short and long plank sizes.
    private static final int SHORT = 3;
    private static final int LONG = 5;

    private static void getLengths(int k, int currentLength,
                                   Set<Integer> lengths) {
        if (k == 0) {
            lengths.add(currentLength);
            return;
        }

        getLengths(k - 1, currentLength + SHORT, lengths);
        getLengths(k - 1, currentLength + LONG, lengths);
    }

    private static Set<Integer> calculate_rec(int k) {
        Set<Integer> lengths = new HashSet<>();
        if (k <= 0) return lengths;

        getLengths(k, 0, lengths);
        return lengths;
    }

    private static Set<Integer> calculate_it(int k) {
        Set<Integer> lengths = new HashSet<>();
        if (k <= 0) return lengths;

        // Base case where all planks are SHORT.
        int base = 0;
        for (int i = 0; i < k; i++) {
            base += SHORT;
        }
        lengths.add(base);

        // Substitute a SHORT with a LONG plank in each iteration.
        for (int i = 0; i < k; i++) {
            base -= SHORT;
            base += LONG;
            lengths.add(base);
        }
        return lengths;
    }

    private static boolean testCalculate_NegativePlanks() {
        Set<Integer> rec = calculate_rec(-1);
        Set<Integer> it = calculate_it(-1);
        return rec.isEmpty() && it.isEmpty();
    }

    private static boolean testCalculate_ZeroPlanks() {
        Set<Integer> rec = calculate_rec(0);
        Set<Integer> it = calculate_it(0);
        return rec.isEmpty() && it.isEmpty();
    }

    private static boolean testCalculate_Rec() {
        Set<Integer> results = calculate_rec(3);
        return 4 == results.size() &&
               results.contains(9) &&
               results.contains(11) &&
               results.contains(13) &&
               results.contains(15);
    }

    private static boolean testCalculate_It() {
        Set<Integer> results = calculate_it(3);
        return 4 == results.size() &&
               results.contains(9) &&
               results.contains(11) &&
               results.contains(13) &&
               results.contains(15);
    }

    private static boolean testCalculate() {
        for (int i = -20; i <= 20; i++) {
           Set<Integer> rec = calculate_rec(i);
           Set<Integer> it = calculate_it(i);
           if (!rec.equals(it)) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testCalculate_NegativePlanks()) {
            counter++;
            System.out.println("Negative planks calculation test failed.");
        }
        if (!testCalculate_ZeroPlanks()) {
            counter++;
            System.out.println("Zero planks calculation test failed.");
        }
        if (!testCalculate_Rec()) {
            counter++;
            System.out.println("Recursive calculation test failed.");
        }
        if (!testCalculate_It()) {
            counter++;
            System.out.println("Iterative calculation test failed.");
        }
        if (!testCalculate()) {
            counter++;
            System.out.println("Calculation test failed.");
        }
        System.out.println(counter + " tests failed.");
    }
}

