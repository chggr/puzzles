import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

// Task description: Given a dictionary and two words of equal length, write a
// method to transform one word into another by changing only one letter at a
// time. The new word you get in each step must be in the dictionary.
//
// E.g. for input "DAMP" and "LIKE"
//      the method should return "DAMP" -> "LAMP" -> "LIMP" -> "LIME" -> "LIKE"
//
// Solution: It is helpful in this task to imagine a graph that links each word
// in the dictionary with all other words that have a distance of one letter.
// The requirement is to traverse the graph from a starting node to a target and
// return the path that has been followed.
//
// The first challenge is how to find all adjacent nodes for a given node, i.e.
// all other words in the graph that differ in only one letter. This can be done
// in three ways: (1) Create all possible transformations of the word and then
// filter out the ones that are not in the dictionary, (2) Go through all words
// in the dictionary and keep only the ones where their distance from the given
// word is only one and (3) pre-process the dictionary into a map that contains
// entries so that all words that are one edit away are grouped together. In the
// implementations below we have used approaches (2) and (3).
//
// The first implementation below is depth first. We keep track of all the words
// already visited in each path to avoid infinite loops. The same method is
// called recursively, going deep into the graph until it either finds a path or
// backtracks. This method will find a path if one exists, but does not guarantee
// that the returned path will be the shortest path overall. The runtime
// complexity of this approach is O(V + E) where V is the number of vertices in
// the graph (i.e. distinct words in the dictionary) and E is the number of
// edges (i.e. words that differ only in one letter).
//
// The second implementation is breadth first, which first goes wide before going
// deep. If there are multiple paths connecting the start and end nodes, breadth
// first search is guaranteed to return the shortest one and run faster. If the
// two nodes are quite close, depth first search might take a very long, windy
// path to find a connection, whereas depth first search will identify it much
// faster in practice. The runtime complexity of this approach is also O(V + E).
//
// Finally the third implementation is a double breadth first search because it
// searches from the source and destination nodes simultaneously. The shortest
// path between the two nodes is identified as soon as the two searches collide.
// The runtime complexity of a single BFS can also be described as O(B^D)),
// where B is the branching factor of the graph (i.e. the average number of out
// edges of each node) and D is the distance between the start and end nodes. In
// case of double BFS the runtime complexity is O(B ^ (D / 2)), i.e. the square
// root of a single BFS.

public class WordTransformer {

    private static final Set<String> DICT = new HashSet<>(Arrays.asList(
                "DAMP", "LIKE", "LIMP", "LAMP", "LIME", "LESS", "MORE"));

    // Calculates the distance between two words.
    private static int distance(String a, String b) {
        if (a.length() != b.length()) {
            return Integer.MAX_VALUE;
        }

        int distance = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a.charAt(i) != b.charAt(i)) distance++;
        }
        return distance;
    }

    // Finds all words in the dictionary with distance at most one.
    private static Set<String> getWords(Set<String> dict, String w) {
        Set<String> result = new HashSet<>();
        for (String word : dict) {
            if (distance(word, w) == 1) result.add(word);
        }
        return result;
    }

    // Pre-processes the dictionary so that words that are one edit away are
    // grouped together, e.g.one entry could be LI_E = [LIKE, LIME].
    private static Map<String, List<String>> preprocess(Set<String> dict) {
        Map<String, List<String>> map = new HashMap<>();
        for (String word : dict) {
            char[] chars = word.toCharArray();

            for (int i = 0; i < chars.length; i++) {
                char temp = chars[i];
                chars[i] = '_';
                String key = new String(chars);
                chars[i] = temp;

                map.computeIfAbsent(key, (k) -> new ArrayList<>());
                map.get(key).add(word);
            }
        }
        return map;
    }

    // Finds all words in a pre-processed dictionary with distance at most one.
    private static Set<String> getWords(Map<String, List<String>> map, String w) {
        char[] chars = w.toCharArray();
        Set<String> result = new HashSet<>();
        for (int i = 0; i < chars.length; i++) {
            char temp = chars[i];
            chars[i] = '_';
            List<String> list = map.get(new String(chars));
            if (list != null) result.addAll(list);
            chars[i] = temp;
        }
        return result;
    }

    // Uses depth first search to transform one word to another.
    private static List<String> transformDFS(Set<String> dict,
                                             Set<String> visited,
                                             List<String> path,
                                             String target) {

        if (path == null || path.isEmpty()) return new ArrayList<>();

        String lastWord = path.get(path.size() - 1);
        if (lastWord.equals(target)) return path;

        Set<String> words = getWords(dict, lastWord);
        for (String word : words) {
            if (visited.contains(word)) continue;

            visited.add(word);
            path.add(word);

            List<String> result = transformDFS(dict, visited, path, target);
            if (!result.isEmpty()) return result;

            path.remove(word);
            visited.remove(word);
        }
        return new ArrayList<>();
    }

    private static List<String> transformDFS(Set<String> dict, String a, String b) {
        Set<String> visited = new HashSet<>();
        List<String> path = new ArrayList<>();
        path.add(a);
        return transformDFS(dict, visited, path, b);
    }

    // Class to hold graph path information, much like a linked list.
    private static class PathNode {
        String word;
        PathNode previous;

        public PathNode(String word, PathNode previous) {
            this.word = word;
            this.previous = previous;
        }
    }

    // Collapses a path into a list of words.
    private static List<String> collapse(PathNode p) {
        List<String> result = new ArrayList<>();
        while (p != null) {
            result.add(0, p.word);
            p = p.previous;
        }
        return result;
    }

    // Uses one way depth first search to transform one word to another.
    private static List<String> transformBFS(Set<String> dict, String a, String b) {
        Map<String, List<String>> newDict = preprocess(dict);

        Queue<PathNode> queue = new LinkedList<>();
        queue.add(new PathNode(a, null));

        Set<String> visited = new HashSet<>();
        visited.add(a);

        PathNode target = null;
        while (!queue.isEmpty()) {
            PathNode current = queue.remove();
            Set<String> words = getWords(newDict, current.word);
            for (String word : words) {
                if (visited.contains(word)) continue;
                if (word.equals(b)) {
                    return collapse(new PathNode(word, current));
                }

                visited.add(word);
                queue.add(new PathNode(word, current));
            }
        }
        return new ArrayList<>();
    }

    // Collapses a left and right path of a double BFS into a list of words.
    private static List<String> collapse(PathNode left, PathNode right) {
        List<String> result = collapse(left);
        while (right != null) {
            result.add(right.word);
            right = right.previous;
        }
        return result;
    }

    private static List<String> transformBFS2(Set<String> dict,
                                              String a, String b) {

        Map<String, List<String>> newDict = preprocess(dict);

        PathNode aNode = new PathNode(a, null);
        Queue<PathNode> fromQ = new LinkedList<>();
        fromQ.add(aNode);
        Map<String, PathNode> fromVisited = new HashMap<>();
        fromVisited.put(a, aNode);

        PathNode bNode = new PathNode(b, null);
        Queue<PathNode> toQ = new LinkedList<>();
        toQ.add(bNode);
        Map<String, PathNode> toVisited = new HashMap<>();
        toVisited.put(b, bNode);

        while(!fromQ.isEmpty() || !toQ.isEmpty()) {

            if (!fromQ.isEmpty()) {
                PathNode current = fromQ.remove();
                Set<String> words = getWords(newDict, current.word);
                for (String word : words) {
                    if (fromVisited.keySet().contains(word)) continue;
                    if (toVisited.keySet().contains(word)) {
                        return collapse(current, toVisited.get(word));
                    }

                    PathNode next = new PathNode(word, current);
                    fromVisited.put(word, next);
                    fromQ.add(next);
                }
            }

            if (!toQ.isEmpty()) {
                PathNode current = toQ.remove();
                Set<String> words = getWords(newDict, current.word);
                for (String word : words) {
                    if (toVisited.keySet().contains(word)) continue;
                    if (fromVisited.keySet().contains(word)) {
                        return collapse(fromVisited.get(word), current);
                    }

                    PathNode next = new PathNode(word, current);
                    toVisited.put(word, next);
                    toQ.add(next);
                }
            }
        }
        return new ArrayList<>();
    }

    private static boolean testDictionaryEmpty() {
        List<String> dfs = transformDFS(new HashSet<>(), "DAMP", "LIKE");
        List<String> bfs = transformBFS(new HashSet<>(), "DAMP", "LIKE");
        List<String> bfs2 = transformBFS2(new HashSet<>(), "DAMP", "LIKE");

        return dfs.isEmpty() && bfs.isEmpty() && bfs2.isEmpty();
    }

    private static boolean testTransformNotExists() {
        List<String> dfs = transformDFS(DICT, "MORE", "LESS");
        List<String> bfs = transformBFS(DICT, "MORE", "LESS");
        List<String> bfs2 = transformBFS(DICT, "MORE", "LESS");

        return dfs.isEmpty() && bfs.isEmpty() && bfs2.isEmpty();
    }

    private static boolean testTransformExists() {
        List<String> dfs = transformDFS(DICT, "DAMP", "LIKE");
        List<String> bfs = transformBFS(DICT, "DAMP", "LIKE");
        List<String> bfs2 = transformBFS2(DICT, "DAMP", "LIKE");
        List<String> expected = Arrays.asList("DAMP", "LAMP", "LIMP", "LIME", "LIKE");

        return dfs.equals(expected) &&
               bfs.equals(expected) &&
               bfs2.equals(expected);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testDictionaryEmpty()) {
            counter++;
            System.out.println("Dictionary empty test failed!");
        }
        if (!testTransformNotExists()) {
            counter++;
            System.out.println("Transformation does not exist test failed!");
        }
        if (!testTransformExists()) {
            counter++;
            System.out.println("Transformation exists test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

