import java.util.PriorityQueue;

// Task description: Given a nearly sorted array of integers, where each number
// is at most k positions away from its target position, what sorting algorithm
// should we use to achieve the best runtime complexity?
//
// Solution: One sorting algorithm that can be used to sort the nearly sorted
// array is insertion sort. The runtime complexity of this approach is O(N * K)
// where N is the number of elements in the array and K the maximum number of
// positions each element is away from its target position. This is because we
// would have to go through the array N times, each time moving the element up
// to K positions to sort it.
//
// The implementation below uses a min heap to sort the array more efficiently.
// We initially add the first K elements in the min heap. We then remove the min
// element from the heap, placing it in the resulting array while at the same
// time adding a new element to the heap from the remaining elements in the
// array. Add and remove operations in the min heap take O(logK) and therefore
// the overall complexity is O(N * logK), since each element in the array will
// need to be added and removed from the heap once.

public class NearlySortedArray {

    public static void sort(int[] input, int k) {
        if (input.length < k) return;

        PriorityQueue<Integer> queue = new PriorityQueue<>(k);
        for (int i = 0; i < k; i++) {
            queue.offer(input[i]);
        }

        for (int i = 0; i < input.length; i++) {
            input[i] = queue.poll();
            if (i + k < input.length) {
                queue.offer(input[i + k]);
            }
        }
    }

    private static boolean isSorted(int[] array) {
        for (int i = 1; i < array.length; i++) {
            if (array[i - 1] > array[i]) return false;
        }
        return true;
    }

    private static boolean testEmpty() {
        int[] array = {};
        sort(array, 3);
        return 0 == array.length;
    }

    private static boolean testSorted() {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        sort(array, 3);
        return isSorted(array);
    }

    private static boolean testUnsorted() {
        int[] array = {2, 1, 3, 7, 5, 9, 4, 8, 6};
        sort(array, 4);
        return isSorted(array);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty array test failed!");
        }
        if (!testSorted()) {
            counter++;
            System.out.println("Sorted array test failed!");
        }
        if (!testUnsorted()) {
            counter++;
            System.out.println("Unsorted array test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

