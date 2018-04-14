// Task description: Given a singly linked list, implement the merge sort
// algorithm to sort the nodes by their value.
//
// E.g. for input 4 => 9 => 7 => 5 => 1 => 2 => 8 => 3 => 6
//      return: 1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9
//
// Solution: Merge sort is often the preferred algorithm for sorting a linked
// list because this data structure has very slow random access performance.
// Other sorting algorithms (such as quicksort) require fast random access and
// therefore perform poorly on linked lists. The implementation below uses a
// fast and a slow pointer to initially split the given list in half. It then
// sorts and merges the two halves before returning a reference to the head of
// the sorted list. The runtime complexity of this algorithm is O(N * logN)
// where N is the total number of elements in the list. The space complexity is
// O(1) because the algorithm is not recursive and does not require any extra
// space during merge.

public class ListMergeSort {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node sort(Node head) {
        if (head == null || head.next == null) return head;

        // Split the list in two parts.
        Node slow = head;
        Node fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        Node left = head;
        Node right = slow.next;
        slow.next = null;

        // Sort the two halves.
        left = sort(left);
        right = sort(right);

        // Merge sorted halves.
        Node newHead = null;
        Node current = null;
        while (left != null && right != null) {
            if (left.value <= right.value) {
                if (current == null) {
                    current = left;
                    newHead = left;
                } else {
                    current.next = left;
                    current = current.next;
                }
                left = left.next;
            } else {
                if (current == null) {
                    current = right;
                    newHead = right;
                } else {
                    current.next = right;
                    current = current.next;
                }
                right = right.next;
            }
        }

        if (left != null) current.next = left;
        if (right != null) current.next = right;
        return newHead;
    }

    private static Node buildList(int... data) {
        if (data.length == 0) return null;

        Node head = new Node(data[0]);
        Node current = head;
        for (int i = 1; i < data.length; i++) {
            Node node = new Node(data[i]);
            current.next = node;
            current = current.next;
        }
        return head;
    }

    private static boolean assertList(Node expected, Node actual) {
        while (actual != null && expected != null) {
            if (actual.value != expected.value) return false;
            actual = actual.next;
            expected = expected.next;
        }
        return actual == null && expected == null;
    }

    private static boolean testNull() {
        return null == sort(null);
    }

    private static boolean testOneElement() {
        Node input = buildList(1);
        return assertList(input, sort(input));
    }

    private static boolean testSorted() {
        Node input = buildList(1, 2, 3, 4, 5, 6, 7, 8, 9);
        return assertList(input, sort(input));
    }

    private static boolean testReverseSorted() {
        Node input = buildList(9, 8, 7, 6, 5, 4, 3, 2, 1);
        Node expected = buildList(1, 2, 3, 4, 5, 6, 7, 8, 9);
        return assertList(expected, sort(input));
    }

    private static boolean testUnsorted() {
        Node input = buildList(4, 9, 7, 5, 1, 2, 8, 3, 6);
        Node expected = buildList(1, 2, 3, 4, 5, 6, 7, 8, 9);
        return assertList(expected, sort(input));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNull()) {
            counter++;
            System.out.println("Null list test failed!");
        }
        if (!testOneElement()) {
            counter++;
            System.out.println("One element list test failed!");
        }
        if (!testSorted()) {
            counter++;
            System.out.println("List already sorted test failed!");
        }
        if (!testReverseSorted()) {
            counter++;
            System.out.println("List reverse sorted test failed!");
        }
        if (!testUnsorted()) {
            counter++;
            System.out.println("List unsorted test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

