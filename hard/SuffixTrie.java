import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

// Task description: Given a big, immutable text file, write a method to perform
// repetitive searches for various patterns. The runtime should be proportional
// to the length of the pattern rather than the length of the text.
//
// Solution: There are multiple algorithms that perform pattern matching on a
// large string, such as Knuth-Morris-Pratt, Rabin-Karb, etc. All these
// algorithms pre-process the pattern to speed up searching. The best runtime
// complexity they can achieve is O(T), where T is the length of the text. If
// the text is large, immutable and searched often (e.g. works by Shakespeare),
// we need to pre-process the text instead of the pattern so that we can run
// queries in time O(P), proportional to the length of the pattern.
//
// Below we have implemented a suffix trie, which is like a normal trie but
// contains all suffixes of the given text. This allows us to perform searches
// in O(P), but unfortunately uses a lot of space. To reduce space requirements,
// we can compress the trie by compacting chains of redundant nodes (i.e. work
// from the leafs upwards, compressing nodes that have only one child). The data
// structure created after compressing the suffix trie is called a suffix tree.
//
// Suffix trees store all the T*(T-1)/2 suffixes of the text in O(T) space and
// support pattern matching and prefix matching queries in O(P) time. There are
// efficient algorithms that allow construction in just O(T) time. Common
// queries that can be answered with suffix trees are:
// (1) Does a pattern exist in the text?
// (2) Is a pattern a suffix of the text?
// (3) How many times does the pattern appear in the text?
// (4) What is the longest repeating pattern in the text?
// (5) What is the longest common substring of the pattern and the text?

public class SuffixTrie {

    private static final class TrieNode {
        public Map<Character, TrieNode> children = new HashMap<>();
        public boolean leaf = false;
    }

    private TrieNode root;

    public SuffixTrie(String text) {
        root = new TrieNode();
        for (int i = text.length() - 1; i >= 0; i--) {
            insert(text, i);
        }
    }

    private void insert(String text, int from) {
        TrieNode current = root;
        for (int i = from; i < text.length(); i++) {
            Character c = text.charAt(i);
            if (!current.children.containsKey(c)) {
                current.children.put(c, new TrieNode());
            }
            current = current.children.get(c);
        }
        current.leaf = true;
    }

    private TrieNode searchTrie(String pattern) {
        TrieNode current = root;
        for (int i = 0; i < pattern.length(); i++) {
            current = current.children.get(pattern.charAt(i));
            if (current == null) return null;
        }
        return current;
    }

    public boolean search(String pattern) {
        return searchTrie(pattern) != null;
    }

    public boolean isSuffix(String pattern) {
        TrieNode node = searchTrie(pattern);
        return node != null && node.leaf;
    }

    private int countLeavesFrom(TrieNode node) {
        Queue<TrieNode> queue = new LinkedList<>();
        queue.add(node);

        int count = 0;
        while (!queue.isEmpty()) {
            TrieNode n = queue.remove();
            if (n.leaf) count++;
            queue.addAll(n.children.values());
        }
        return count;
    }

    public int count(String pattern) {
        TrieNode node = searchTrie(pattern);
        if (node == null) return 0;
        return countLeavesFrom(node);
    }

    public static boolean testSearch() {
        SuffixTrie st = new SuffixTrie("the brown fox jumped");
        return st.search("fox") && st.search("jump") &&
               st.search("the") && st.search("ped") &&
               !st.search("one") && !st.search("dog");
    }

    public static boolean testIsSuffix() {
        SuffixTrie st = new SuffixTrie("the brown fox jumped");
        return st.isSuffix("ped") && st.isSuffix("jumped") &&
               !st.isSuffix("fox") && !st.isSuffix("dog");
    }

    public static boolean testCount() {
        SuffixTrie st = new SuffixTrie("the brown fox and the ox");
        return 2 == st.count("ox") && 2 == st.count("the") &&
               1 == st.count("brown") && 0 == st.count("dog");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testSearch()) {
            counter++;
            System.out.println("Search test failed!");
        }
        if (!testIsSuffix()) {
            counter++;
            System.out.println("Is suffix test failed!");
        }
        if (!testCount()) {
            counter++;
            System.out.println("Count test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

