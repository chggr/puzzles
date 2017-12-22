#include <iostream>
#include <stack>
#include <string>

// Task description: Write a method that given any integer will return its
// English translation.
//
// E.g. for 12, the method should return twelve.
//      for 3400, the method should return three thousand four hundred.
//
// Solution: The implementation below splits the given number into segments
// of three digits, translates each segment separately and then joins them by
// inserting the words thousands, millions, billions etc as necessary. A stack
// is used to push the individual words, which is joined back together before
// the method returns the final string.

using namespace std;

string smalls[] = { "", "one", "two", "three", "four", "five", "six",
                    "seven", "eight", "nine", "ten", "eleven", "twelve",
                    "thirteen", "fourteen", "fifteen", "sixteen",
                    "seventeen", "eighteen", "nineteen" };

string tens[] = { "", "", "twenty", "thirty", "forty", "fifty", "sixty",
                  "seventy", "eighty", "ninety" };

string bigs[] = { "", "", "thousand", "million", "billion", "trillion" };

// Creates a string by joining the strings in the stack.
string to_string(stack<string> &words) {
    string output = "";

    while(!words.empty()) {
        string top = words.top();
        if (!top.empty()) {
            output += top + " ";
        }
        words.pop();
    }
    return output;
}

string to_english(int n) {
    if (n == 0) return "zero ";
    string sign = "";
    stack<string> words;

    int smalls_idx = 0;
    int tens_idx = 0;
    int hundreds = 0;
    int bigs_idx = 0;

    if (n < 0) {
        sign = "negative ";
        n = -n;
    }

    while (n > 0) {

        // Extract next three digit segment.
        int seg = n % 1000;
        n /= 1000;
        bigs_idx++;
        if (seg == 0) continue;

        // Analyze segment.
        if (seg % 100 < 20) {
            smalls_idx = seg % 100;
            tens_idx = 0;
        } else {
            smalls_idx = seg % 10;
            tens_idx = (seg / 10) % 10;
        }
        hundreds = (seg / 100) % 10;

        // Push words into the stack.
        words.push(bigs[bigs_idx]);
        words.push(smalls[smalls_idx]);
        words.push(tens[tens_idx]);
        if (hundreds > 0) {
            words.push("hundred");
            words.push(smalls[hundreds]);
        }
    }

    return sign + to_string(words);
}

int test_zero() {
    return "zero " == to_english(0) &&
           "zero " == to_english(-0);
}

int test_tens() {
    return "one " == to_english(1) &&
           "negative one " == to_english(-1) &&
           "twelve " == to_english(12) &&
           "nineteen " == to_english(19) &&
           "negative fifteen " == to_english(-15) &&
           "negative eleven " == to_english(-11);
}

int test_hundreds() {
    return "one hundred twenty three " == to_english(123) &&
           "negative two hundred one " == to_english(-201) &&
           "nine hundred twelve " == to_english(912) &&
           "negative eight hundred thirty six " == to_english(-836) &&
           "six hundred ninety nine " == to_english(699);
}

int test_millions() {
    cout << to_english(-1000001) << endl;
    return "negative one million one " == to_english(-1000001) &&
           "nine hundred million nine hundred thousand nine "
               "hundred " == to_english(900900900) &&
            "negative one hundred eleven million one hundred eleven "
               "thousand one hundred eleven " == to_english(-111111111) &&
            "nine hundred ninety nine million nine hundred ninety nine "
               "thousand nine hundred ninety nine " == to_english(999999999);
}

int main() {
    int counter = 0;
    if (!test_zero()) {
        cout << "Zero test failed!" << endl;
        counter++;
    }
    if (!test_tens()) {
        cout << "Tens test failed!" << endl;
        counter++;
    }
    if (!test_hundreds()) {
        cout << "Hundreds test failed!" << endl;
        counter++;
    }
    if (!test_millions()) {
        cout << "Millions test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

