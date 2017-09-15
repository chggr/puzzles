// Task description: Given the head to a singly linked list and a number p,
// write a method to partition the list based on p, so that all nodes with
// values less than p come before all nodes with values greater or equal to p.
//
// E.g. For list 3 => 5 => 1 => 2 => 4 and p = 3,
//      the method should return: 2 => 1 => 3 => 5 => 4
//
// Solution: Two implementations have been provided below, one stable (i.e.
// attempts to retain the order of the elements in the original list as much as
// possible) and one unstable (i.e. does not care about the order of elements
// in the original list).
//
// The stable solution creates two new lists, one of them to hold items less
// than the given number and the other to hold items greater than or equal to
// the given number. It iterates through the original list, adding each element
// to the correct list. At the end it joins the list and returns the new head.
//
// The unstable solution maintains two new pointers, one at the head and one at
// the tail. It iterates through the original list and adds each element before
// head or after tail according to whether it is greater than or less than the
// given number.

public class ListPartition {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node partition(Node head, int p) {
        Node current = head;
        Node tail = head;

        while (current != null) {
            Node next = current.next;
            if (current.value > p) {
                tail.next = current;
                tail = current;
            } else if (current.value <= p) {
                current.next = head;
                head = current;
            }
            tail.next = null;
            current = next;
        }
        return head;
    }

    private static Node partitionStable(Node head, int p) {
        Node smallerHead = null;
        Node smallerTail = null;
        Node largerHead = null;
        Node largerTail = null;
        Node current = head;

        while (current != null) {
            Node next = current.next;
            if (current.value > p) {
                if (largerHead == null) {
                    largerHead = current;
                    largerTail = current;
                } else {
                    largerTail.next = current;
                    largerTail = current;
                    largerTail.next = null;
                }
            } else if (current.value < p) {
                if (smallerHead == null) {
                    smallerHead = current;
                    smallerTail = current;
                } else {
                    smallerTail.next = current;
                    smallerTail = current;
                    smallerTail.next = null;
                }
            } else {
                if (largerHead == null) {
                    largerHead = current;
                    largerTail = current;
                } else {
                    current.next = largerHead;
                    largerHead = current;
                }
            }
            current = next;
        }

        if (smallerHead == null) {
            return largerHead;
        }
        smallerTail.next = largerHead;
        return smallerHead;
    }

    private static boolean testStable_NullHead() {
        return null == partitionStable(null, 1);
    }

    private static boolean testUnstable_NullHead() {
        return null == partition(null, 1);
    }

    private static boolean testStable_OneElement() {
        Node head = new Node(1);
        head = partitionStable(head, 2);
        return 1 == head.value && null == head.next;
    }

    private static boolean testUnstable_OneElement() {
        Node head = new Node(1);
        head = partition(head, 2);
        return 1 == head.value && null == head.next;
    }

    private static boolean testStable_TwoElements() {
        Node head = new Node(2);
        head.next = new Node(1);
        head = partitionStable(head, 1);
        return 1 == head.value && 2 == head.next.value;
    }

    private static boolean testUnStable_TwoElements() {
        Node head = new Node(2);
        head.next = new Node(1);
        head = partition(head, 1);
        return 1 == head.value && 2 == head.next.value;
    }

    private static boolean testStable_AlreadyPartitioned() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        head.next.next.next.next = new Node(5);
        
        head = partitionStable(head, 3);
        return 1 == head.value &&
               2 == head.next.value &&
               3 == head.next.next.value &&
               4 == head.next.next.next.value &&
               5 == head.next.next.next.next.value;
    }

    private static boolean testUnstable_AlreadyPartitioned() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        head.next.next.next.next = new Node(5);
        
        head = partition(head, 3);
        return 3 == head.value &&
               2 == head.next.value &&
               1 == head.next.next.value &&
               4 == head.next.next.next.value &&
               5 == head.next.next.next.next.value;
    }

    private static boolean testStable_NotPartitioned() {
        Node head = new Node(3);
        head.next = new Node(5);
        head.next.next = new Node(1);
        head.next.next.next = new Node(2);
        head.next.next.next.next = new Node(4);
        
        head = partitionStable(head, 3);
        return 1 == head.value &&
               2 == head.next.value &&
               3 == head.next.next.value &&
               5 == head.next.next.next.value &&
               4 == head.next.next.next.next.value;
    }

    private static boolean testUnstable_NotPartitioned() {
        Node head = new Node(3);
        head.next = new Node(5);
        head.next.next = new Node(1);
        head.next.next.next = new Node(2);
        head.next.next.next.next = new Node(4);
        
        head = partition(head, 3);
        return 2 == head.value &&
               1 == head.next.value &&
               3 == head.next.next.value &&
               5 == head.next.next.next.value &&
               4 == head.next.next.next.next.value;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testStable_NullHead()) {
            counter++;
            System.out.println("Test stable with null head failed!");
        }
        if (!testUnstable_NullHead()) {
            counter++;
            System.out.println("Test unstable with null head failed!");
        }
        if (!testStable_OneElement()) {
            counter++;
            System.out.println("Test stable with one element failed!");
        }
        if (!testUnstable_OneElement()) {
            counter++;
            System.out.println("Test unstable with one element failed!");
        }
        if (!testStable_TwoElements()) {
            counter++;
            System.out.println("Test stable with two elements failed!");
        }
        if (!testUnStable_TwoElements()) {
            counter++;
            System.out.println("Test unstable with two elements failed!");
        }
        if (!testStable_AlreadyPartitioned()) {
            counter++;
            System.out.println("Test stable with already partitioned list failed!");
        }
        if (!testUnstable_AlreadyPartitioned()) {
            counter++;
            System.out.println("Test unstable with already partitioned list failed!");
        }
        if (!testStable_NotPartitioned()) {
            counter++;
            System.out.println("Test stable with not partitioned list failed!");
        }
        if (!testUnstable_NotPartitioned()) {
            counter++;
            System.out.println("Test unstable with not partitioned list failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

