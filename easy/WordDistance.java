import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a large text file and two words, find the shortest
// distance (in terms of number of words) between them in the file. What is the
// runtime complexity? How can the operation be optimized for performance if it
// is carried out multiple times against the same file but different pairs of
// words?
//
// E.g. for text file containing the words:
//      {"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"}
//      the distance between "fox" and "dog" is 5.
//
// Solution: The first implementation below traverses the list of words in the
// file just once, keeping track where each of the words was seen last time and
// updating their minimum distance. The runtime complexity of this algorithm is
// O(n), where n is the total number of words in the file.
//
// The second implementation can be used if we need to repeat this operation
// against the same file multiple times. We first build a map that contains a
// list of positions for each word in the file. The runtime and space complexity
// of this preprocessing step is O(n). Once the map is constructed, it can be
// used multiple times to efficiently find the minimum distance between any two
// words.

public class WordDistance {

    public static int minDistance(String[] words, String wordA, String wordB) {
        int posA = -1;
        int posB = -1;
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < words.length; i++) {
            if (wordA.equals(words[i])) posA = i;
            if (wordB.equals(words[i])) posB = i;
            if (posA > 0 && posB > 0 && Math.abs(posA - posB) < min) {
                min = Math.abs(posA - posB);
            }
        }
        return min;
    }

    private static Map<String, List<Integer>> buildPositionMap(String[] words) {
        Map<String, List<Integer>> map = new HashMap<>();
        for (int i = 0; i < words.length; i++) {
            if (!map.containsKey(words[i])) {
                map.put(words[i], new ArrayList<>());
            }
            map.get(words[i]).add(i);
        }
        return map;
    }

    public static int minDistance2(String[] words, String wordA, String wordB) {
        Map<String, List<Integer>> map = buildPositionMap(words);
        List<Integer> posA = map.get(wordA);
        List<Integer> posB = map.get(wordB);

        int min = Integer.MAX_VALUE;
        if (posA == null || posB == null) return min;

        int indexA = 0;
        int indexB = 0;
        while(indexA < posA.size() && indexB < posB.size()) {
            if (Math.abs(posA.get(indexA) - posB.get(indexB)) < min) {
                min = Math.abs(posA.get(indexA) - posB.get(indexB));
            }

            if (posA.get(indexA) < posB.get(indexB)) {
                indexA++;
            } else {
                indexB++;
            }
        }
        return min;
    }

    private static final String[] SENTENCE = {"the", "quick", "brown", "fox",
        "jumped", "over", "the", "lazy", "dog"};

    private static boolean testMinDistance() {
        return 5 == minDistance(SENTENCE, "fox", "dog") &&
               5 == minDistance(SENTENCE, "dog", "fox") &&
               5 == minDistance2(SENTENCE, "fox", "dog") &&
               5 == minDistance2(SENTENCE, "dog", "fox") &&
               2 == minDistance(SENTENCE, "the", "dog") &&
               2 == minDistance(SENTENCE, "dog", "the") &&
               2 == minDistance2(SENTENCE, "the", "dog") &&
               2 == minDistance2(SENTENCE, "dog", "the");
    }

    private static boolean testMinDistance_OneMissing() {
        return Integer.MAX_VALUE == minDistance(SENTENCE, "fox", "lion") &&
               Integer.MAX_VALUE == minDistance(SENTENCE, "lion", "fox") &&
               Integer.MAX_VALUE == minDistance2(SENTENCE, "fox", "lion") &&
               Integer.MAX_VALUE == minDistance2(SENTENCE, "lion", "fox");
    }

    private static boolean testMinDistance_BothMissing() {
        return Integer.MAX_VALUE == minDistance(SENTENCE, "cat", "lion") &&
               Integer.MAX_VALUE == minDistance(SENTENCE, "lion", "cat") &&
               Integer.MAX_VALUE == minDistance2(SENTENCE, "cat", "lion") &&
               Integer.MAX_VALUE == minDistance2(SENTENCE, "lion", "cat");
    }

    private static boolean testMinDistance_SameWord() {
        return 0 == minDistance(SENTENCE, "the", "the") &&
               0 == minDistance2(SENTENCE, "the", "the");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testMinDistance()) {
            System.out.println("Min distance test failed!");
            counter++;
        }
        if (!testMinDistance_OneMissing()) {
            System.out.println("Min distance, one word missing test failed!");
            counter++;
        }
        if (!testMinDistance_BothMissing()) {
            System.out.println("Min distance, both words missing test failed!");
            counter++;
        }
        if (!testMinDistance_SameWord()) {
            System.out.println("Min distance, same word test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

