import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;

// Task description: Given a dictionary and an array of char, find a word in
// the dictionary that uses as many of the provided characters as possible.
// The array of char could contain the same character multiple times, but each
// array entry should only be used once. This task solves the popular game
// "Scrabble". If the dictionary is empty or no word can be found, the method
// should return an empty String.
//
// E.g For input {'R', 'R', 'E', 'Z', 'D'} the answer is "ERR".
//     For input {'T', 'C', 'W', 'A', 'G'} the answer is "ACT".
//     For input {} the answer is "".
public class Scrabble {

    private static final String DICT_URL = "/usr/share/dict/british-english";
    private static final Set<String> DICT = new HashSet<>();

    private static String find(Set<String> dictionary, char[] letters) {
        String result = "";
        for (String word : dictionary) {
            List<Character> wordLetters = new ArrayList<>();
            for (Character c : word.toCharArray()) {
                wordLetters.add(c);
            }
            for (Character c : letters) {
                wordLetters.remove(c);
            }
            if (wordLetters.isEmpty() && word.length() > result.length()) {
                result = word;
            }
        }
        return result;
    }

    private static void loadDictionary() throws IOException {
        try (FileReader fr = new FileReader(DICT_URL);
             BufferedReader br = new BufferedReader(fr)) {

            String word;
            while ((word = br.readLine()) != null) {
                word = word.toUpperCase(Locale.ENGLISH);
                if (!word.matches("[A-Z]*") || word.length() < 2) {
                    continue;
                }
                DICT.add(word);
            }
        }
    }

    private static boolean testEmptyDictionary() {
        return "".equals(find(new HashSet<>(), new char[]{'A', 'B', 'C', 'D'}));
    }

    private static boolean testEmptyCharArray() {
        return "".equals(find(DICT, new char[]{}));
    }

    private static boolean testRepeatedCharacters() {
        return "ERR".equals(find(DICT, new char[]{'R', 'R', 'E', 'Z', 'D'}));
    }

    private static boolean testNonRepeatedCharacters() {
        return "ACT".equals(find(DICT, new char[]{'T', 'C', 'W', 'A', 'G'}));
    }

    private static boolean testNoResult() {
        return "".equals(find(DICT, new char[]{'Z', 'W', 'T', 'G', 'X'}));
    }

    public static void main(String[] args) throws IOException {
        loadDictionary();

        int counter = 0;
        if (!testEmptyDictionary()) {
            System.out.println("Empty dictionary test failed!");
            counter++;
        }
        if (!testEmptyCharArray()) {
            System.out.println("Empty character array test failed!");
            counter++;
        }
        if (!testRepeatedCharacters()) {
            System.out.println("Repeated characters test failed!");
            counter++;
        }
        if (!testNonRepeatedCharacters()) {
            System.out.println("Non repeated characters test failed!");
            counter++;
        }
        if (!testNoResult()) {
            System.out.println("No result test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

