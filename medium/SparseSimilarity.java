import static java.util.Arrays.asList;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: The similarity of two documents, each with distinct words,
// is defined as the size of their intersection divided by the size of their
// union. Given a long list of documents, each associated with a unique id,
// design an algorithm that returns a list of pairs of document ids and their
// associated similarity where that is not zero.
//
// E.g. the similarity of {1, 5, 3} and {1, 7, 2, 3} is 2 / 5 = 0.4
//
//      for the following input:
//      13 : {14, 15, 100, 9, 3}
//      16 : {32, 1, 9, 3, 5}
//      19 : {15, 29, 2, 6, 8, 7}
//      24 : {7, 10}
//
//      the method should return:
//      {13, 19} : 0.1
//      {13, 16} : 0.25
//      {19, 24} : 0.142857
//
// Solution: The first implementation below uses a brute force approach to
// calculate the similarity for all pairs of documents. If D is the total number
// of documents and W is the average word count in each document, the runtime
// complexity of this algorithm is O(D^2 * W^2). This is because we compare all
// possible pairs of documents and for each pair we compute the similarity score
// by checking whether each word on the first document exists in the second
// document as well. A small optimization can be made in method similarity() if
// we put all words of one document into a Set. This would take O(N) but then
// lookups take just O(1). Thus the complexity can be reduced from O(N^2) to
// O(N).
//
// The second implementation first transforms the list of documents into a map
// that maps each word to a list of documents ids it appears in. This makes it
// simpler to calculate the similarities of each pair of documents: we just need
// to iterate through the map and for each word get the list of documents it
// appears in. Then for every pair of documents, increment the count of words
// they have in common. Once this is done for all words, we can then go through
// the pair of documents with words in common and calculate their similarity
// score. If D is the total number of documents, W is the average word count
// in each document and P is the number of pairs of documents with similarity
// score greater than zero, the runtime complexity of this approach is
// O(P * W + D * W). This is because we need to transform the original list
// of documents into a map which takes O(D * W). Moreover for each word in the
// map we need to calculate the pair of documents that have this word in common,
// which takes O(P * W). The space complexity is O(P + W + D).

public class SparseSimilarity {

    private static final class Pair<T> {
        private final T one;
        private final T two;

        public Pair(T one, T two) {
            this.one = one;
            this.two = two;
        }

        public T getOne() {
            return one;
        }

        public T getTwo() {
            return two;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Pair)) return false;

            Pair<?> other = (Pair<?>) o;
            return this.one.equals(other.one) &&
                   this.two.equals(other.two);
        }

        @Override
        public int hashCode() {
            int result = 17;
            result = result * 37 + one.hashCode();
            result = result * 37 + two.hashCode();
            return result;
        }
    }

    private static final class Document {
        private final int id;
        private final List<Integer> words;

        public Document(int id, List<Integer> words) {
            this.id = id;
            this.words = words;
        }

        public int getId() {
            return id;
        }

        public List<Integer> getWords() {
            return words;
        }
    }

    // Computes similarity score between two documents.
    private static double similarity(Document a, Document b) {
        int inBoth = 0;
        for (Integer word : a.getWords()) {
            if (b.getWords().contains(word)) inBoth++;
        }
        return inBoth * 1.0 / (a.getWords().size() + b.getWords().size() - inBoth);
    }

    private static Map<Pair<Integer>, Double> calculateBrute(List<Document> documents) {
        Map<Pair<Integer>, Double> results = new HashMap<>();
        for (int i = 0; i < documents.size(); i++) {
            for (int j = i + 1; j < documents.size(); j++) {
                Document a = documents.get(i);
                Document b = documents.get(j);

                double score = similarity(a, b);
                if (score > 0) {
                    results.put(new Pair<>(a.getId(), b.getId()), score);
                }
            }
        }
        return results;
    }

    // Creates a map of word to list of document ids it appears in.
    private static Map<Integer, List<Integer>> wordMap(List<Document> documents) {
        Map<Integer, List<Integer>> map = new HashMap<>();
        for (Document doc : documents) {
            for (Integer word : doc.getWords()) {
                if (!map.containsKey(word)) {
                    map.put(word, new ArrayList<>());
                }
                map.get(word).add(doc.getId());
            }
        }
        return map;
    }

    // Creates a map of document id to document.
    private static Map<Integer, Document> documentMap(List<Document> documents) {
        Map<Integer, Document> documentMap = new HashMap<>();
        for (Document document : documents) {
            documentMap.put(document.getId(), document);
        }
        return documentMap;
    }

    // Creates a pair, always using the smallest integer as first element.
    private static Pair<Integer> createPair(Integer a, Integer b) {
        return a < b ? new Pair<>(a, b) : new Pair<>(b, a);
    }

    // Returns a map of pairs of documents to the count of words they have in common.
    private static Map<Pair<Integer>, Double> similarities(List<Document> documents) {
        Map<Pair<Integer>, Double> results = new HashMap<>();
        Map<Integer, List<Integer>> wordMap = wordMap(documents);

        for (Integer word : wordMap.keySet()) {
            List<Integer> docIds = wordMap.get(word);
            for (int i = 0; i < docIds.size(); i++) {
                for (int j = i + 1; j < docIds.size(); j++) {
                    Pair<Integer> pair = createPair(docIds.get(i), docIds.get(j));
                    if (!results.containsKey(pair)) {
                        results.put(pair, 1.0);
                    } else {
                        results.put(pair, results.get(pair) + 1);
                    }
                }
            }
        }
        return results;
    }

    private static Map<Pair<Integer>, Double> calculateOpt(List<Document> documents) {
        Map<Integer, Document> docMap = documentMap(documents);
        Map<Pair<Integer>, Double> similarities = similarities(documents);

        for (Pair<Integer> pair : similarities.keySet()) {
            double union = docMap.get(pair.getOne()).getWords().size() +
                           docMap.get(pair.getTwo()).getWords().size() -
                           similarities.get(pair);
            similarities.put(pair, similarities.get(pair) / union);
        }
        return similarities;
    }

    private static final Document A = new Document(1, asList(1, 2, 3));
    private static final Document B = new Document(2, asList(3, 2, 1));
    private static final Document C = new Document(3, asList(3, 4, 5));
    private static final Document D = new Document(4, asList(4, 5, 6));
    private static final Document E = new Document(5, new ArrayList<>());

    private static boolean testSimilarity() {
        return 1.0 == similarity(A, A) &&
               1.0 == similarity(A, B) &&
               1.0 == similarity(B, A) &&
               0.2 == similarity(A, C) &&
               0.2 == similarity(C, A) &&
               0.0 == similarity(A, D) &&
               0.0 == similarity(D, A) &&
               0.0 == similarity(A, E) &&
               0.0 == similarity(E, A);
    }

    private static boolean testCalculateBrute() {
        List<Document> documents = new ArrayList<>();
        documents.add(new Document(13, asList(12, 15, 100, 9, 3)));
        documents.add(new Document(16, asList(32, 1, 9, 3, 5)));
        documents.add(new Document(19, asList(15, 29, 2, 6, 8, 7)));
        documents.add(new Document(24, asList(7, 2, 10, 11)));

        Map<Pair<Integer>, Double> results = calculateBrute(documents);
        return 3 == results.size() &&
               0.1 == results.get(new Pair<>(13, 19)) &&
               0.25 == results.get(new Pair<>(13, 16)) &&
               0.25 == results.get(new Pair<>(19, 24));
    }

    private static boolean testWordMap() {
        Map<Integer, List<Integer>> wordMap = wordMap(asList(A, B, C, D, E));
        return 6 == wordMap.size() &&
               wordMap.get(1).equals(asList(1, 2)) &&
               wordMap.get(2).equals(asList(1, 2)) &&
               wordMap.get(3).equals(asList(1, 2, 3)) &&
               wordMap.get(4).equals(asList(3, 4)) &&
               wordMap.get(5).equals(asList(3, 4)) &&
               wordMap.get(6).equals(asList(4));
    }

    private static boolean testDocumentMap() {
        Map<Integer, Document> docMap = documentMap(asList(A, B, C, D, E));
        return 5 == docMap.size() &&
               docMap.get(1).equals(A) &&
               docMap.get(2).equals(B) &&
               docMap.get(3).equals(C) &&
               docMap.get(4).equals(D) &&
               docMap.get(5).equals(E);
    }

    private static boolean testCreatePair() {
        Pair<Integer> pairA = createPair(1, 2);
        Pair<Integer> pairB = createPair(2, 1);
        return pairA.equals(pairB);
    }

    private static boolean testSimilarities() {
        Map<Pair<Integer>, Double> similarities = similarities(asList(A, B, C, D, E));
        return 4 == similarities.size() &&
               3.0 == similarities.get(new Pair<>(1, 2)) &&
               2.0 == similarities.get(new Pair<>(3, 4)) &&
               1.0 == similarities.get(new Pair<>(1, 3)) &&
               1.0 == similarities.get(new Pair<>(2, 3));
    }

    private static boolean testCalculateOpt() {
        List<Document> documents = new ArrayList<>();
        documents.add(new Document(13, asList(12, 15, 100, 9, 3)));
        documents.add(new Document(16, asList(32, 1, 9, 3, 5)));
        documents.add(new Document(19, asList(15, 29, 2, 6, 8, 7)));
        documents.add(new Document(24, asList(7, 2, 10, 11)));

        Map<Pair<Integer>, Double> results = calculateOpt(documents);
        return 3 == results.size() &&
               0.1 == results.get(new Pair<>(13, 19)) &&
               0.25 == results.get(new Pair<>(13, 16)) &&
               0.25 == results.get(new Pair<>(19, 24));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testSimilarity()) {
            System.out.println("Similarity test failed!");
            counter++;
        }
        if (!testCalculateBrute()) {
            System.out.println("Calculate brute test failed!");
            counter++;
        }
        if (!testWordMap()) {
            System.out.println("Word map test failed!");
            counter++;
        }
        if (!testDocumentMap()) {
            System.out.println("Document map test failed!");
            counter++;
        }
        if (!testCreatePair()) {
            System.out.println("Create pair test failed!");
            counter++;
        }
        if (!testSimilarities()) {
            System.out.println("Similarities test failed!");
            counter++;
        }
        if (!testCalculateOpt()) {
            System.out.println("Calculate optimal test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

