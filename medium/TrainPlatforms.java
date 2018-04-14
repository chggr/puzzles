import java.util.Arrays;

// Task description: Given the arrival and departure times of all trains that
// reach a railway station, find the minimum number of platforms required so
// that no train waits.
//
// E.g. for arrival times    {900,  940,  950, 1100, 1500, 1800}
//      and departure times  {910, 1200, 1120, 1130, 1900, 2000}
//      the method should return: 3
//
// Solution: The fist implementation below is a brute force approach. For every
// train arrival we go through all remaining arrivals to count the number of
// overlaps. We keep track and return the maximum number of overlaps. The
// runtime complexity of this approach is O(n^2), where n is the number of train
// arrivals.
//
// The second implementation uses a greedy approach to calculate the maximum
// number of platforms required. It first sorts the arrays with the arrival and
// departure times and then picks up the next item in sequence from both arrays.
// It increments the current number of trains on platforms accordingly, keeping
// track and returning the maximum number of platforms required. The runtime
// complexity of this approach is O(n * logn) required for sorting the arrays.
//
// Finally the third implementation uses an array that holds the balance of
// trains arriving and departing in the station at any given minute of the day.
// This array is updated using the given arrival and departure times. Finally we
// traverse through the array, keeping track of the maximum number of trains
// present in the station at any given minute. The runtime complexity of this
// approach is O(n) and space complexity O(1) since the size of the balance
// array does not depend on the size of the input.

public class TrainPlatforms {

    private static int calculate_brute(int[] arr, int[] dep) {
        int max = 0;
        for (int i = 0; i < arr.length; i++) {
            int current = 1;
            for (int j = i + 1; j < arr.length; j++) {
                if ((arr[j] > arr[i] && arr[j] < dep[i]) ||
                    (dep[j] > arr[i] && dep[j] < dep[i])) {
                    current++;
                }
            }
            if (current > max) max = current;
        }
        return max;
    }

    private static int calculate_greedy(int[] arr, int[] dep) {
        Arrays.sort(arr);
        Arrays.sort(dep);

        int max = 0;
        int current = 0;
        int arrIdx = 0;
        int depIdx = 0;
        while (arrIdx < arr.length &&
               depIdx < dep.length) {
            if (arr[arrIdx] < dep[depIdx]) {
                current++;
                arrIdx++;
            } else {
                current--;
                depIdx++;
            }
            if (current > max) max = current;
        }
        return max;
    }

    private static int calculate_opt(int[] arr, int[] dep) {
        int[] balance = new int[2400];
        for (int i = 0; i < arr.length; i++) balance[arr[i]]++;
        for (int i = 0; i < dep.length; i++) balance[dep[i]]--;

        int max = 0;
        int current = 0;
        for (int i = 0; i < balance.length; i++) {
            current += balance[i];
            if (current > max) max = current;
        }
        return max;
    }

    public static boolean testEmpty() {
        int[] arr = new int[0];
        int[] dep = new int[0];
        return 0 == calculate_brute(arr, dep) &&
               0 == calculate_greedy(arr, dep) &&
               0 == calculate_opt(arr, dep);
    }

    public static boolean testOverlap() {
        int[] arr = {900,  940,  950, 1100, 1500, 1800};
        int[] dep = {910, 1200, 1120, 1130, 1900, 2000};
        return 3 == calculate_brute(arr, dep) &&
               3 == calculate_greedy(arr, dep) &&
               3 == calculate_opt(arr, dep);
    }

    public static boolean testNoOverlap() {
        int[] arr = {900,  940, 1210, 1300, 1500, 1910};
        int[] dep = {910, 1200, 1220, 1330, 1900, 2000};
        return 1 == calculate_brute(arr, dep) &&
               1 == calculate_greedy(arr, dep) &&
               1 == calculate_opt(arr, dep);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty test failed!");
        }
        if (!testOverlap()) {
            counter++;
            System.out.println("Overlap test failed!");
        }
        if (!testNoOverlap()) {
            counter++;
            System.out.println("No overlap test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

