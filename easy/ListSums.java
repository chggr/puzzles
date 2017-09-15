// Task description: A number can be represented as a singly linked list, where
// each node contains a single digit. The digits can be stored in MSB - Most
// Significant Bit first or LSB - Least Significant Bit first format. Write
// two methods (MSB and LSB) that will accept two lists and return the head to
// a list containing the sum.
//
// E.g. For LSB input lists: 1 => 2 => 3 (number 321) and 4 => 5 (number 54)
//         output should be: 5 => 7 => 3 (number 375)
//
//      For MSB input lists: 1 => 2 => 3 (number 123) and 4 => 5 (number 45)
//         output should be: 1 => 6 => 8 (number 168)

public class ListSums {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node listSumLSB(Node head1, Node head2) {
        return getListLSB(getNumberLSB(head1) + getNumberLSB(head2));
    }

    private static Node listSumMSB(Node head1, Node head2) {
        return getListMSB(getNumberMSB(head1) + getNumberMSB(head2));
    }

    private static int getNumberLSB(Node head) {
        int number = 0;
        int counter = 0;

        while (head != null) {
            number += head.value * Math.pow(10, counter++);
            head = head.next;
        }
        return number;
    }

    private static int getNumberMSB(Node head) {
        int number = 0;

        while (head != null) {
            number = number * 10 + head.value;
            head = head.next;
        }
        return number;
    }

    private static Node getListLSB(int number) {
        Node head = null;
        Node current = null;

        while (number > 0) {
            Node node = new Node(number % 10);
            number /= 10;
            if (head == null) {
                head = node;
                current = node;
            } else {
                current.next = node;
                current = node;
            }
        }
        return head;
    }

    private static Node getListMSB(int number) {
        Node head = null;

        while (number > 0) {
            Node node = new Node(number % 10);
            number /= 10;
            node.next = head;
            head = node;
        }
        return head;
    }

    private static boolean testListSumLSB_NullHeads() {
        return null == listSumLSB(null, null);
    }

    private static boolean testListSumMSB_NullHeads() {
        return null == listSumMSB(null, null);
    }

    private static boolean testListSumLSB_OneNullHead() {
        Node head = new Node(1);
        head.next = new Node(2);

        Node result = listSumLSB(head, null);
        return 1 == result.value && 2 == result.next.value;
    }

    private static boolean testListSumMSB_OneNullHead() {
        Node head = new Node(1);
        head.next = new Node(2);

        Node result = listSumMSB(head, null);
        return 1 == result.value && 2 == result.next.value;
    }

    private static boolean testListSumLSB() {
        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);

        Node head2 = new Node(4);
        head2.next = new Node(5);

        Node result = listSumLSB(head1, head2);
        return 5 == result.value &&
               7 == result.next.value &&
               3 == result.next.next.value;
    }

    private static boolean testListSumMSB() {
        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);

        Node head2 = new Node(4);
        head2.next = new Node(5);

        Node result = listSumMSB(head1, head2);
        return 1 == result.value &&
               6 == result.next.value &&
               8 == result.next.next.value;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testListSumLSB_NullHeads()) {
            System.out.println("List sum LSB with null heads test failed!");
            counter++;
        }
        if (!testListSumMSB_NullHeads()) {
            System.out.println("List sum MSB with null heads test failed!");
            counter++;
        }
        if (!testListSumLSB_OneNullHead()) {
            System.out.println("List sum LSB with one null head test failed!");
            counter++;
        }
        if (!testListSumMSB_OneNullHead()) {
            System.out.println("List sum MSB with one null head test failed!");
            counter++;
        }
        if (!testListSumLSB()) {
            System.out.println("List sum LSB test failed!");
            counter++;
        }
        if (!testListSumMSB()) {
            System.out.println("List sum MSB test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

