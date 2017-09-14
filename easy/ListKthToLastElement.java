// Task description: Given the head of a simply linked list and an integer k,
// write a method that will return the kth to last element of the list.
//
// E.g. For list 1 => 2 => 3 => 4 and k = 1 it should return 4
//                                    k = 2 it should return 3
//
// Solution: This problem can be solved either recursively or iteratively.
// Recursive solutions are often simpler and shorter but less optimal. For
// example in this case a recursive solution takes O(N) space, whereas the
// iterative solution only O(1).
//
// A recursive algorithm would go through the list and when it hits the end
// would pass back a counter set to zero. Each parent call would increment the
// counter by one until it becomes equal to k. At that point we would have
// reached the kth to last element in the list. We could print that element or
// or set it in a static variable.
//
// The iterative algorithm implemented below uses two pointers (current and
// runner) to find the kth to last element in the list. At the beginning it
// moves the runner k positions from head and then increments both pointers
// until the runner has reached to the end. At that point current will be
// pointing at the kth to last element.

public class ListKthToLastElement {

    private static final class Node {
        private final int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node kthToLast(Node head, int k) {
        Node current = head;
        Node runner = head;

        for (int i = 0; i < k; i++) {
            if (runner == null) {
                return null;
            }
            runner = runner.next;
        }

        while (runner != null) {
            runner = runner.next;
            current = current.next;
        }
        return current;
    }

    private static boolean testNullHead() {
        return null == kthToLast(null, 3);
    }

    private static boolean testShortList() {
        Node head = new Node(1);
        head.next = new Node(2);
        return null == kthToLast(head, 3);
    }

    private static boolean testLongList() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        return 3 == kthToLast(head, 2).value &&
               4 == kthToLast(head, 1).value;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNullHead()) {
            System.out.println("Null head test failed!");
            counter++;
        }
        if (!testShortList()) {
            System.out.println("Short list test failed!");
            counter++;
        }
        if (!testLongList()) {
            System.out.println("Long list test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

