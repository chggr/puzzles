// Task description: Implement a BTree.
//
// Solution: A BTree is a self balancing tree that keeps the data sorted and
// allows searcing, insertions and deletions in O(logN) time. It is a
// generalization of a binary tree, where each node can have more that two
// children. BTrees are optimized for systems that read and write large blocks
// of data, such as filesystems and databases.
//
// In BTrees, internal nodes can have a variable number of child nodes within
// a predefined range that is usually fixed for a particular implementation. As
// data is inserted or deleted, the number of child nodes can change and thus
// nodes are often joined or split to maintain this property. The number of
// child nodes for each give node is always equal to one more than the number of
// keys stored in the node.
//
// A BTree is kept balanced by required that all leaf nodes are at the same
// depth. The height of the tree will slowly increase as more data is added to
// the tree, but such an increase is not very frequent. This data structure has
// substantial advantages when the time to access the data of a node greatly
// exceeds the time spent processing it. By maximizing the number of keys within
// each node, the height of the tree decreases and therefore the number of
// expensive read operations is reduced.
//
// Inserting data into a BTree typically starts at a leaf node. We first need to
// search and find the leaf node where the data needs to be added. The data is
// then inserted into that node in sorted order and no further action is taken
// if the node is not yet full. On the contrary, if the node is full, it needs
// to be split into two as follows:
//
// (1) The median value is chosen.
// (2) Values less than the median are put in the left node and values greater
//     than the median in the right node. The median acts as a separation value.
// (3) The median is inserted in the node's parent, which may again cause it to
//     be split in a recursive fashion.
// (4) If the node has no parent (i.e. is the root), a new root is created and
//     the height of the tree increases.

public class BTree<K extends Comparable<K>, V> {

    // Maximum children per BTree node is M - 1.
    private static final int M = 4;

    // Represents a BTree node that holds an array of entries.
    private static final class Node {
        private int length = 0;
        private Entry[] children = new Entry[M];
    }

    // An entry to a BTree node.
    // Internal nodes have value equal to null.
    // Leaf nodes have next equal to null.
    private static final class Entry<K, V> {
        private K key;
        private V value;
        private Node next;

        public Entry(K key, V value, Node next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }
    }

    private Node root = new Node();
    private int height = 0;
    private int size = 0;

    /** Returns true if the BTree is empty. */
    public boolean isEmpty() {
        return size == 0;
    }

    /** Returns the number of key - value pairs in the BTree. */
    public int size() {
        return size;
    }

    /** Returns the BTree height. */
    public int height() {
        return height;
    }

    /** Returns the value associated with a given key */
    public V get(K key) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null");
        }
        return search(root, key, height);
    }

    // Searches the BTree for a particular key.
    private V search(Node node, K key, int height) {

        // Reached the leaf level.
        if (height == 0) {
            for (int i = 0; i < node.length; i++) {
                if (node.children[i].key.equals(key)) {
                    return (V) node.children[i].value;
                }
            }
            return null;
        }

        // Internal node.
        for (int i = 0; i < node.length; i++) {
            if (i + 1 == node.length ||
                    key.compareTo((K) node.children[i + 1].key) < 0) {
                return search(node.children[i].next, key, height - 1);
            }
        }
        return null;
    }

    /**
     * Inserts the key-value pair into the BTree, overwritting the old value
     * with the new value if the key already exists in the BTree. If the value
     * is null, this effectively deletes the key from the BTree.
     */
    public void put(K key, V value) {
        if (key == null) {
            throw new IllegalArgumentException();
        }

        Node n = insert(root, key, value, height);
        size++;

        // Need to split root.
        if (n != null) {
            Node newRoot = new Node();
            newRoot.length = 2;
            newRoot.children[0] = new Entry(root.children[0].key, null, root);
            newRoot.children[1] = new Entry(n.children[0].key, null, n);
            root = newRoot;
            height++;
        }
    }

    // Inserts a key-value pair into the BTree.
    private Node insert(Node node, K key, V value, int height) {
        int pos;
        Entry newEntry = new Entry(key, value, null);

        if (height == 0) {

            // Reached the leaf level.
            for (pos = 0; pos < node.length; pos++) {
                if (key.compareTo((K) node.children[pos].key) < 0) {
                    break;
                }
            }

        } else {

            // Internal node.
            for (pos = 0; pos < node.length; pos++) {
                if (pos + 1 == node.length ||
                        key.compareTo((K) node.children[pos + 1].key) < 0) {
                    Node n = insert(node.children[pos++].next, key, value, height - 1);
                    if (n == null) return null;
                    newEntry.key = n.children[0].key;
                    newEntry.next = n;
                    break;
                }
            }
        }

        for (int i = node.length; i > pos; i--) {
            node.children[i] = node.children[i - 1];
        }
        node.children[pos] = newEntry;
        node.length++;
        return node.length < M ? null : split(node);
    }

    // Splits the given node into two, returns the new node.
    private Node split(Node node) {
        Node newNode = new Node();
        newNode.length = node.length / 2;
        node.length -= newNode.length;

        // Copy the right half of node.children into new node.
        for (int i = 0; i < newNode.length; i++) {
            newNode.children[i] = node.children[node.length + i];
        }
        return newNode;
    }

    private static boolean testEmpty() {
        BTree<Integer, String> btree = new BTree<>();
        return 0 == btree.size() && 0 == btree.height() && btree.isEmpty();
    }

    private static boolean testPutGet() {
        BTree<Integer, String> btree = new BTree<>();
        btree.put(1, "one");
        btree.put(2, "two");
        btree.put(3, "three");
        btree.put(4, "four");
        btree.put(5, "five");
        btree.put(6, "six");
        btree.put(7, "seven");
        btree.put(8, "eight");

        return 2 == btree.height() && 8 == btree.size() &&
               "one".equals(btree.get(1)) && "two".equals(btree.get(2)) &&
               "three".equals(btree.get(3)) && "four".equals(btree.get(4)) &&
               "five".equals(btree.get(5)) && "six".equals(btree.get(6)) &&
               "seven".equals(btree.get(7)) && "eight".equals(btree.get(8));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmpty()) {
            counter++;
            System.out.println("Empty test failed!");
        }
        if (!testPutGet()) {
            counter++;
            System.out.println("Put / Get test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

