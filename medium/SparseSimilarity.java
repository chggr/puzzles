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

public class SparseSimilarity {

    private static final class Pair<T> {
        private final T one;
        private final T two;

        public Pair(T one, T two) {
            this.one = one;
            this.two = two;
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

    private static boolean testSimilarity() {
        Document a = new Document(1, asList(1, 2, 3));
        Document b = new Document(2, asList(3, 2, 1));
        Document c = new Document(3, asList(3, 4, 5));
        Document d = new Document(4, asList(4, 5, 6));
        Document empty = new Document(5, new ArrayList<>());

        return 1.0 == similarity(a, a) &&
               1.0 == similarity(a, b) &&
               1.0 == similarity(b, a) &&
               0.2 == similarity(a, c) &&
               0.2 == similarity(c, a) &&
               0.0 == similarity(a, d) &&
               0.0 == similarity(d, a) &&
               0.0 == similarity(a, empty) &&
               0.0 == similarity(empty, a);
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
        System.out.println(counter + " tests failed.");
    }
}

