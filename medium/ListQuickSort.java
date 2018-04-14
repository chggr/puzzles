// Task description: Given a singly linked list, implement the quick sort
// algorithm to sort the nodes by their value.
//
// E.g. for input 4 => 9 => 7 => 5 => 1 => 2 => 8 => 3 => 6
//      return: 1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9
//
// Solution: The implementation below using quick sort to sort the given singly
// linked list. It uses the head element as the pivot and creates three sub
// lists to store elements less than, equal to and greater than the pivot. Once
// this partitioning is done, it calls itself recursively to sort the two lists
// that store elements less than and equal to the pivot. Finally it links all
// three sub-lists together and returns the head to the final result. The
// runtime complexity of this algorithm is O(N * logN), where N is the number of
// nodes in the list. Space complexity is O(logN) for the recursive stack.

public class ListQuickSort {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node sort(Node head) {
        if (head == null || head.next == null) return head;

        // Define lists to hold elements with values less, equal
        // or more than the head, whose value is used as pivot.
        Node lessHead = null;
        Node lessCurrent = null;
        Node moreHead = null;
        Node moreCurrent = null;
        Node equalHead = head;
        Node equalCurrent = head;

        // Partition the list.
        Node current = head.next;
        head.next = null;
        while (current != null) {
            if (current.value == equalHead.value) {
                equalCurrent.next = current;
                equalCurrent = equalCurrent.next;
                current = current.next;
                equalCurrent.next = null;
            } else if (current.value < equalHead.value) {
                if (lessCurrent == null) {
                    lessCurrent = current;
                    lessHead = current;
                } else {
                    lessCurrent.next = current;
                    lessCurrent = lessCurrent.next;
                }
                current = current.next;
                lessCurrent.next = null;
            } else {
                if (moreCurrent == null) {
                    moreCurrent = current;
                    moreHead = current;
                } else {
                    moreCurrent.next = current;
                    moreCurrent = moreCurrent.next;
                }
                current = current.next;
                moreCurrent.next = null;
            }
        }

        // Recursively sort elements less or more than pivot.
        lessHead = sort(lessHead);
        moreHead = sort(moreHead);

        // Link the sub-lists together to form final result.
        equalCurrent.next = moreHead;
        if (lessHead != null) {
            Node lessTail = lessHead;
            while (lessTail.next != null) lessTail = lessTail.next;
            lessTail.next = equalHead;
            return lessHead;
        }
        return equalHead;
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

    public static boolean testNull() {
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

    private static boolean testDuplicates() {
        Node input = buildList(5, 2, 8, 6, 2, 5, 7, 9, 5);
        Node expected = buildList(2, 2, 5, 5, 5, 6, 7, 8, 9);
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
        if (!testDuplicates()) {
            counter++;
            System.out.println("List with duplicates test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

