import java.util.PriorityQueue;

// Task description: Given a string that continuously generates random integers,
// create a class to find the median value as new values are generated.
//
// Solution: The first implementation below uses an array to store the data and
// return the median. When a new value is added, it is always placed as the last
// element in the array and is then continuously swapped with the element at the
// left as long as that element is greater. Thus it is using an algorithm similar
// to insertion sort to bubble up each element to the correct position so that
// the array remains always sorted. The runtime complexity of adding elements to
// this data structure is O(n), but returning the median is just O(1). Dynamic
// array resizing can be added to allow the array to expand as more and more
// values are added.
//
// The second implementation below is using two heaps: a max-heap for all values
// below the median and a min-heap for all values above the median. This divides
// the elements roughly in half, with the middle two elements at the top of the
// two heaps. This makes it trivial to find the median. When a new value arrives
// it is placed in the lowerHalf heap if the value is less than or equal to the
// median, otherwise it is placed in the upperHalf heap. The heaps are then
// rebalanced so that either their sizes are equal or the upperHalf heap
// contains at most one extra element. The median is available in constant O(1)
// time and adding extra elements takes O(logn) time.

public class MedianStream {

    public static final class ArrayMedian {
        private int[] array;
        private int cursor;

        public ArrayMedian(int capacity) {
            this.array = new int[capacity];
            this.cursor = 0;
        }

        public void add(int number) {
            array[cursor] = number;

            for (int i = cursor; i > 0; i--) {
                if (array[i] >= array[i - 1]) break;
                int temp = array[i - 1];
                array[i - 1] = array[i];
                array[i] = temp;
            }
            cursor++;
        }

        public double median() {
            if (cursor == 0) return 0;
            if (cursor % 2 == 1) return array[cursor / 2];
            return (array[cursor / 2] + array[cursor / 2 - 1]) / 2.0;
        }
    }

    public static final class HeapsMedian {

        // max-heap for the lower half of the data.
        private final PriorityQueue<Integer> lowerHalf =
            new PriorityQueue<>(10, (a, b) -> a > b ? -1 : a < b ? 1 : 0);

        // min-heap for the upper half of the data.
        private final PriorityQueue<Integer> upperHalf =
            new PriorityQueue<>(10, (a, b) -> a > b ? 1 : a < b ? -1 : 0);

        public void add(int number) {
            // Add number to lower or upper half.
            if (lowerHalf.peek() != null &&
                number <= lowerHalf.peek()) {
                lowerHalf.offer(number);
            } else {
                upperHalf.offer(number);
            }

            // Balance the heaps so that upperHalf size is either
            // equal or one greater than the lowerHalf size.
            if (lowerHalf.size() > upperHalf.size()) {
                upperHalf.offer(lowerHalf.poll());
            }
            if (upperHalf.size() - 1 > lowerHalf.size()) {
                lowerHalf.offer(upperHalf.poll());
            }
        }

        public double median() {
            if (upperHalf.size() == 0) return 0.0;
            if (lowerHalf.size() != upperHalf.size()) return upperHalf.peek();
            return (lowerHalf.peek() + upperHalf.peek()) / 2.0;
        }
    }

    private static boolean testEmpty() {
        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();

        return 0.0 == array.median() && 0.0 == heaps.median();
    }

    private static boolean testOneElement() {
        ArrayMedian array = new ArrayMedian(10);
        array.add(5);

        HeapsMedian heaps = new HeapsMedian();
        heaps.add(5);

        return 5.0 == array.median() && 5.0 == heaps.median();
    }

    private static boolean testTwoElements() {
        ArrayMedian array = new ArrayMedian(10);
        array.add(5);
        array.add(2);

        HeapsMedian heaps = new HeapsMedian();
        heaps.add(5);
        heaps.add(2);

        return 3.5 == array.median() && 3.5 == heaps.median();
    }

    private static boolean testThreeElements() {
        int[] data = {5, 4, 7};

        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();
        for (int i = 0; i < data.length; i++) {
            array.add(data[i]);
            heaps.add(data[i]);
        }

        return 5.0 == array.median() && 5.0 == heaps.median();
    }

    private static boolean testOddElements() {
        int[] data = {5, 2, 7, 3, 9, 11, 1};

        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();
        for (int i = 0; i < data.length; i++){
            array.add(data[i]);
            heaps.add(data[i]);
        }

        return 5.0 == array.median() && 5.0 == heaps.median();
    }

    private static boolean testEvenElements() {
        int[] data = {5, 2, 7, 3, 9, 11, 1, 4};

        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();
        for (int i = 0; i < data.length; i++) {
            array.add(data[i]);
            heaps.add(data[i]);
        }

        return 4.5 == array.median() && 4.5 == heaps.median();
    }

    private static boolean testNegativeElements() {
        int[] data = {-2, 5, 9, -7, -3, 6, -1};

        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();
        for (int i = 0; i < data.length; i++) {
            array.add(data[i]);
            heaps.add(data[i]);
        }

        return -1.0 == array.median() && -1.0 == heaps.median();
    }

    private static boolean testSameElements() {
        ArrayMedian array = new ArrayMedian(10);
        HeapsMedian heaps = new HeapsMedian();
        for (int i = 0; i < 7; i++) {
            array.add(1);
            heaps.add(1);
        }

        return 1.0 == array.median() && 1.0 == heaps.median();
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmpty()) {
            System.out.println("Empty test failed!");
            counter++;
        }
        if (!testOneElement()) {
            System.out.println("One element test failed!");
            counter++;
        }
        if (!testTwoElements()) {
            System.out.println("Two elements test failed!");
            counter++;
        }
        if (!testThreeElements()) {
            System.out.println("Three elements test failed!");
            counter++;
        }
        if (!testOddElements()) {
            System.out.println("Odd elements test failed!");
            counter++;
        }
        if (!testEvenElements()) {
            System.out.println("Even elements test failed!");
            counter++;
        }
        if (!testNegativeElements()) {
            System.out.println("Negative elements test failed!");
            counter++;
        }
        if (!testSameElements()) {
            System.out.println("Same elements test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

