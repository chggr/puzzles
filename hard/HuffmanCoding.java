import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

// Task description: Implement Huffman coding to compress a huge text file.
//
// E.g. for input string "ababcad"
//      the Huffman codes are: a => 0, b => 10, c => 110, d => 111
//
// Solution: Huffman coding is a lossless compression algorithm that assigns
// variable length codes to input characters based on their frequency in the
// given text. More frequent characters are represented with fewer bits than
// less frequent characters. The variable length codes are prefix codes, which
// means that they are assigned in such a way so that the code for one character
// is not a prefix of any other code assigned to other characters. This is
// required to ensure there is no ambiguity when encoding into or decoding from
// a bit stream.
//
// The implementation below initially analyzes the input string and calculates
// the frequency of each character. It then uses a min-heap to build the Huffman
// tree: a leaf node is created for all characters that contains their frequency
// and added to the min-heap. We then continuously take two nodes from the heap
// and combine them into a parent node until there is only one node available in
// the heap (i.e. the tree root). Finally the Huffman codes are derived from the
// Huffman tree using a simple recursive method to traverse the tree and collect
// the codes.

public class HuffmanCoding {

    // A node in the Huffman tree.
    private static final class Node implements Comparable<Node> {
        private char c;
        private double freq;
        private Node left;
        private Node right;

        public Node(char c, double freq) {
            this.c = c;
            this.freq = freq;
        }

        @Override
        public int compareTo(Node other) {
            double diff = this.freq - other.freq;
            return diff == 0.0 ? 0 : diff > 0 ? 1 : -1;
        }
    }

    // Calculates the frequencies of all characters in the string.
    private static double[] getFrequencies(String s) {
        double[] freq = new double[26];
        int total = 0;

        for (char c : s.toCharArray()) {
            if (c < 'a' || c > 'z') continue;
            freq[c - 'a']++;
            total++;
        }

        for (int i = 0; i < freq.length; i++) {
            freq[i] /= total;
        }
        return freq;
    }

    // Builds a Huffman tree based on given frequencies.
    private static Node buildTree(double[] freq) {

        // Create a min-heap, add all leaf nodes.
        PriorityQueue<Node> queue = new PriorityQueue<>(freq.length);
        for (int i = 0; i < freq.length; i++) {
            if (freq[i] == 0) continue;
            queue.offer(new Node((char) ('a' + i), freq[i]));
        }

        // Poll the two less frequent nodes and combine them using a parent
        // node. If there is only one node remaining, that is the tree root.
        while (queue.size() > 1) {
            Node one = queue.poll();
            Node two = queue.poll();

            Node parent = new Node(' ', one.freq + two.freq);
            parent.left = one;
            parent.right = two;
            queue.offer(parent);
        }
        return queue.poll();
    }

    // Recursive method responsible for extracting the codes from the tree.
    private static void buildCodes(Node node, String prefix,
                                   Map<Character, String> map) {

        // Leaf node, add the code and return.
        if (node.c != ' ') {
            map.put(node.c, prefix);
            return;
        }

        buildCodes(node.left, prefix + '0', map);
        buildCodes(node.right, prefix + '1', map);
    }

    // Calculates character frequencies, builds the Huffman tree and
    // returns the Huffman code for each character.
    private static Map<Character, String> buildCodes(String s) {
        double[] frequencies = getFrequencies(s);
        Node tree = buildTree(frequencies);
        Map<Character, String> result = new HashMap<>();
        buildCodes(tree, "", result);
        return result;
    }

    private static boolean testSameFrequency() {
        Map<Character, String> map = buildCodes("abcdefg");
        return "100".equals(map.get('a')) &&
               "111".equals(map.get('b')) &&
               "00".equals(map.get('c')) &&
               "011".equals(map.get('d')) &&
               "010".equals(map.get('e')) &&
               "110".equals(map.get('f')) &&
               "101".equals(map.get('g'));
    }

    private static boolean testDifferentFrequency() {
        Map<Character, String> map = buildCodes("ababcad");
        return "0".equals(map.get('a')) &&
               "10".equals(map.get('b')) &&
               "110".equals(map.get('c')) &&
               "111".equals(map.get('d'));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testSameFrequency()) {
            counter++;
            System.out.println("Same character frequency test failed!");
        }
        if (!testDifferentFrequency()) {
            counter++;
            System.out.println("Different character frequency test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

