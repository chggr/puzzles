// Task description: Implement a Trie that supports inserting words in it and
// checking whether given words and prefixes are valid. What is the runtime and
// space complexity of a Trie and when would you use such a data structure?
//
// Solution: A trie is a tree data structure that is typically used to store
// strings. Unlike a binary tree where each node links to a maximum of two other
// nodes (left and right), a node in a trie can link with an arbitrary number of
// nodes, equal to the number of possible values of our data type. For example,
// if we are using a trie to store strings, then the number of possible children
// of each node would be 26, one for each letter of the English alphabet.
//
// The typical application of tries is to store strings and be able to quickly
// check whether the trie contains a given string or a given prefix. Each node
// of the trie corresponds to a single character and the total depth of the
// data structure is equal to the length of the longest word in it. This is in
// contrast to a simple binary tree, where its length is equal to log2(n).
//
// What makes tries perform really well is that the cost of looking up a word or
// prefix is fixed and depends only on the number of characters in the word and
// not in the size of the dictionary. For example, if a dictionary contains n
// words and we store them in a sorted array, word or prefix lookup with binary
// search would take O(logn). We would achieve similar runtime complexity if we
// use a binary tree instead of a sorted array. On the contrary, searching for a
// word or prefix in a trie takes O(1) and is does not depend on how many words
// the trie contains. It depends only on the length of the word or prefix we are
// searching for.
//
// With regards to space requirements, a trie often compresses the dictionary
// because words that have the same root (i.e. home and homely) are not stored
// separately, but the root is stored only once. Nevertheless a trie will often
// require more memory than an array because for each node we need to allocate
// an array of at least 26 pointers to the child nodes. Therefore on a 64 bit
// machine each node will require more than 200 bytes, whereas a single char
// only requires a single byte.

public class Trie {

    private static final class Node {
        private Node[] children = new Node[26];
        private boolean end = false;

        void createChild(char c) {
            if (children[c - 'a'] == null) {
                children[c - 'a'] = new Node();
            }
        }

        Node getChild(char c) {
            return children[c - 'a'];
        }

        void setEnd(boolean value) {
            end = value;
        }

        boolean isEnd() {
            return end;
        }
    }

    private Node root = new Node();

    public void insert(String word) {
        Node current = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            current.createChild(c);
            current = current.getChild(c);
        }
        current.setEnd(true);
    }

    public boolean isWord(String word) {
        Node node = search(word);
        return node != null && node.isEnd();
    }

    public boolean isPrefix(String prefix) {
        Node node = search(prefix);
        return node != null;
    }

    private Node search(String s) {
        Node current = root;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (current.getChild(c) == null) return null;
            current = current.getChild(c);
        }
        return current;
    }

    private static boolean testEmptyTrie() {
        Trie trie = new Trie();

        return !trie.isWord("") &&
               trie.isPrefix("") &&
               !trie.isWord("hello") &&
               !trie.isPrefix("hello");
    }

    private static boolean testTrieDistinctWords() {
        Trie trie = new Trie();
        trie.insert("hello");
        trie.insert("world");

        return !trie.isWord("") &&
               trie.isPrefix("") &&
               trie.isWord("hello") &&
               trie.isWord("world") &&
               trie.isPrefix("hell") &&
               trie.isPrefix("wor") &&
               !trie.isPrefix("be");
    }

    private static boolean testTrie() {
        Trie trie = new Trie();
        trie.insert("house");
        trie.insert("homework");
        trie.insert("home");
        trie.insert("homesick");

        return !trie.isWord("") &&
               trie.isPrefix("") &&
               trie.isWord("house") &&
               trie.isWord("homework") &&
               trie.isWord("home") &&
               trie.isWord("homesick") &&
               trie.isPrefix("ho") &&
               trie.isPrefix("hom") &&
               !trie.isPrefix("ha");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmptyTrie()) {
            System.out.println("Empty trie test failed!");
            counter++;
        }
        if (!testTrieDistinctWords()) {
            System.out.println("Distinct words trie test failed!");
            counter++;
        }
        if (!testTrie()) {
            System.out.println("Trie test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

