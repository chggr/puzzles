#include <iostream>
#include <string>

// Task description: Given two strings, write a method that will detect whether
// they are anagrams. An anagram is the result of rearranging the letters of a
// word to produce a new word using the original letters exactly once.
//
// E.g. Strings "silent" and "listen" are anagrams.
//      Strings "silent" and "test" are not anagrams.

bool isAnagram(std::string a, std::string b) {
	if (a.length() != b.length()) return false;
	if (a.length() == 0 && b.length() == 0) return false;

	int freq[256];
	for (int i = 0; i < 256; i++) freq[i] = 0;
	for (int i = 0; i < a.length(); i++) freq[a.at(i)]++;
	for (int i = 0; i < b.length(); i++) freq[b.at(i)]--;

	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0) return false;
	}
	return true;
}

bool test_anagram() {
	return isAnagram("silent", "listen");
}

bool test_non_anagram() {
	return !isAnagram("silent", "test");
}

bool test_empty_string() {
	return !isAnagram("", "test");
}

bool test_empty_strings() {
	return !isAnagram("", "");
}

int main() {
	int counter = 0;
	if (!test_anagram()) {
		std::cout << "Anagram test failed!\n";
		counter++;
	}
	if (!test_non_anagram()) {
		std::cout << "Non anagram test failed!\n";
		counter++;
	}
	if (!test_empty_string()) {
		std::cout << "Empty string test failed!\n";
		counter++;
	}
	if (!test_empty_strings()) {
		std::cout << "Empty strings test failed!\n";
		counter++;
	}
	std::cout << counter << " tests failed.\n";
}

