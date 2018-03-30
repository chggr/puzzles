import java.io.IOException;

import java.nio.file.Files;
import java.nio.file.Paths;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Stream;

// Task description: Given a dictionary of thousands of words, design an
// algorithm to create the largest possible rectangle of letters such that every
// row and every column forms a word. All rows must be the same length and all
// columns must be the same height.
//
// Solution: In the implementation below, we first pre-process the dictionary
// and transform it into a map that groups together all words with the same
// length. For each one of these groups we create a Trie, which contains all
// words for that length. We then find the largest possible rectangle by trying
// different widths and lengths that give us the largest possible area and
// attempting to build a rectangle. The build process is recursive: we place
// each word in sequence at each row in the rectangle and then check that the
// columns contain valid prefixes. If not, then we backtrack and try a different
// word. Once all rows have been filled, we double check that the columns form
// valid words and return the final solution. The runtime complexity for
// grouping the words and creating Tries is O(N), where N is the total number
// of words in the dictionary. The runtime complexity of building the rectangle
// itself depends heavily on the language and the words present in the
// dictionary.

public class WordRectangle {

    private static final String DICT_PATH = "/usr/share/dict/british-english";

    private static final class TrieNode {
        private TrieNode[] children = new TrieNode[26];
        private boolean leaf = false;
    }

    // Adds a word to a Trie.
    private void add(TrieNode root, String word) {
        TrieNode current = root;
        for (char c : word.toCharArray()) {
            if (current.children[c - 'A'] == null) {
                current.children[c - 'A'] = new TrieNode();
            }
            current = current.children[c - 'A'];
        }
        current.leaf = true;
    }

    // Finds a prefix in the Trie.
    private TrieNode findPrefix(TrieNode root, String prefix) {
        TrieNode current = root;
        for (char c : prefix.toCharArray()) {
            if (current.children[c - 'A'] == null) return null;
            current = current.children[c - 'A'];
        }
        return current;
    }

    // Builds a Trie using the given set of words.
    private TrieNode buildTrie(Set<String> words) {
        TrieNode root = new TrieNode();
        for (String word : words) add(root, word);
        return root;
    }

    // Reads all words in the dictionary and groups them based on length.
    private Map<Integer, Set<String>> preProcessDictionary() {
        Map<Integer, Set<String>> map = new HashMap<>();

        try (Stream<String> stream = Files.lines(Paths.get(DICT_PATH))) {
            stream.forEach(word -> {

                // Should contain only characters, no digits or symbols.
                if (!word.matches("[a-zA-Z]+")) return;
                word = word.toUpperCase();

                map.computeIfAbsent(word.length(), (k) -> new HashSet<>());
                map.get(word.length()).add(word);
            });
        } catch (IOException e) {
            throw new IllegalStateException("IO error while reading dictionary.");
        }
        return map;
    }

    // Creates a trie for all words having the same length.
    private Map<Integer, TrieNode> buildTries(Map<Integer, Set<String>> dict) {
        Map<Integer, TrieNode> tries = new HashMap<>();
        for (Integer key : dict.keySet()) {
            tries.put(key, buildTrie(dict.get(key)));
        }
        return tries;
    }

    // Returns the maximum of a set of integers.
    private int max(Set<Integer> values) {
        int max = Integer.MIN_VALUE;
        for (Integer value : values) {
            if (value != null && value > max) max = value;
        }
        return max;
    }

    // Validates that the columns in the rectangle either are valid prefixes or
    // form words that exist in the trie.
    private boolean validateColumns(String[] rect,
                                    int height,
                                    int width,
                                    TrieNode root,
                                    boolean fullWords) {

        for (int col = 0; col < width; col++) {
            StringBuilder word = new StringBuilder();
            for (int row = 0; row < height; row++) {
                word.append(rect[row].charAt(col));
            }

            TrieNode node = findPrefix(root, word.toString());
            if (node == null) return false;
            if (fullWords && !node.leaf) return false;
        }
        return true;
    }

    private boolean buildRow(String[] rect, int width, int height, int currentRow,
                             Set<String> words, TrieNode columnTrie) {

        // Rectangle is complete, validate if columns are full words.
        if (currentRow >= rect.length) {
            return validateColumns(rect, height, width, columnTrie, true);
        }

        // Try out placing every word in the current row.
        for (String word : words) {
            rect[currentRow] = word;
            if (!validateColumns(rect, currentRow + 1, width, columnTrie, false)) continue;
            if (buildRow(rect, width, height, currentRow + 1, words, columnTrie)) {
                return true;
            }
        }
        return false;
    }

    // Attempts to build a word rectangle of given width and height.
    private String[] buildRectangle(int width, int height,
                                    Map<Integer, Set<String>> dict,
                                    Map<Integer, TrieNode> tries) {

        if (dict.get(width) == null ||
            dict.get(height) == null) return null;

        TrieNode columnTrie = tries.get(height);
        String[] result = new String[height];
        if (buildRow(result, width, height, 0, dict.get(width), columnTrie)) {
            return result;
        }
        return null;
    }

    // Identifies and returns the largest word rectangle in the dictionary.
    private String[] buildRectangle() {
        System.out.println("Grouping words together based on length.");
        Map<Integer, Set<String>> dict = preProcessDictionary();

        System.out.println("Building tries for all words of the same length.");
        Map<Integer, TrieNode> tries = buildTries(dict);

        int maxLength = max(dict.keySet());
        System.out.println("Word length statistics:");
        for (int i = 1; i < maxLength; i++) {
            Set<String> words = dict.get(i);
            System.out.println(i + " " + (words == null ? 0 : words.size()));
        }

        for (int area = maxLength * maxLength; area > 0; area--) {
            for (int width = 1; width <= maxLength; width++) {
                if (area % width != 0) continue;

                int height = area / width;
                if (height > maxLength || height > width) continue;

                System.out.println("Trying A: " + area + " W: " + width +
                                   " H: " + height);
                String[] rect = buildRectangle(width, height, dict, tries);
                if (rect != null) return rect;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        String[] rectangle = new WordRectangle().buildRectangle();
        for (int i = 0; i < rectangle.length; i++) {
            System.out.println(rectangle[i]);
        }
    }
}

