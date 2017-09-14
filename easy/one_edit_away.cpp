#include <string>
#include <iostream>

// Task description: There are three ways to edit a string: insert a character,
// delete a character or replace a character. Given two input strings, write a
// function that returns true only if the two strings are only up to one edit
// away.

bool is_one_edit_away(std::string a, std::string b) {

    int diff = a.length() > b.length() ?
               a.length() - b.length() :
               b.length() - a.length();
    if (diff >= 2) {
        return false;
    }

    int cursor_a = 0;
    int cursor_b = 0;
    int edits = 0;

    while(cursor_a < a.length() && cursor_b < b.length() && edits < 2) {
        if (a.at(cursor_a) == b.at(cursor_b)) {
            cursor_a++;
            cursor_b++;
        } else if (cursor_b + 1 < b.length() &&
                   a.at(cursor_a) == b.at(cursor_b + 1)) {
            cursor_b++;
            edits++;
        } else if (cursor_a + 1 < a.length() &&
                   a.at(cursor_a + 1) == b.at(cursor_b)) {
            cursor_a++;
            edits++;
        } else {
            cursor_a++;
            cursor_b++;
            edits++;
        }
    }

    return edits + a.length() - cursor_a + b.length() - cursor_b < 2;
}

bool test_identical() {
    return is_one_edit_away("dragon", "dragon");
}

bool test_replacement() {
    return is_one_edit_away("dragon", "drakon");
}

bool test_replacement_beginning() {
    return is_one_edit_away("dragon", "vragon");
}

bool test_replacement_end() {
    return is_one_edit_away("dragon", "dragod");
}

bool test_addition() {
    return is_one_edit_away("dragon", "dragoin");
}

bool test_addition_beginning() {
    return is_one_edit_away("dragon", "adragon");
}

bool test_addition_end() {
    return is_one_edit_away("dragon", "dragons");
}

bool test_removal() {
    return is_one_edit_away("dragon", "dagon");
}

bool test_removal_beginning() {
    return is_one_edit_away("dragon", "ragon");
}

bool test_removal_end() {
    return is_one_edit_away("dragon", "drago");
}

bool test_many_replacements() {
    return !is_one_edit_away("dragon", "vrakon");
}

bool test_many_additions() {
    return !is_one_edit_away("dragon", "adragoins");
}

bool test_many_removals() {
    return !is_one_edit_away("dragon", "daon");
}

bool test_mixed() {
    return !is_one_edit_away("dragon", "vagons");
}

int main() {
    int counter = 0;
    if (!test_identical()) {
        counter++;
        std::cout << "Identical test failed." << std::endl;
    }
    if (!test_replacement()) {
        counter++;
        std::cout << "Replacement test failed." << std::endl;
    }
    if (!test_replacement_beginning()) {
        counter++;
        std::cout << "Replacement at beginning test failed." << std::endl;
    }
    if (!test_replacement_end()) {
        counter++;
        std::cout << "Replacement at end test failed." << std::endl;
    }
    if (!test_addition()) {
        counter++;
        std::cout << "Addition test failed." << std::endl;
    }
    if (!test_addition_beginning()) {
        counter++;
        std::cout << "Addition at beginning test failed." << std::endl;
    }
    if (!test_addition_end()) {
        counter++;
        std::cout << "Addition at end test failed." << std::endl;
    }
    if (!test_removal()) {
        counter++;
        std::cout << "Removal test failed." << std::endl;
    }
    if (!test_removal_beginning()) {
        counter++;
        std::cout << "Removal at beginning test failed." << std::endl;
    }
    if (!test_removal_end()) {
        counter++;
        std::cout << "Removal at end test failed." << std::endl;
    }
    if (!test_many_replacements()) {
        counter++;
        std::cout << "Many replacements test failed." << std::endl;
    }
    if (!test_many_additions()) {
        counter++;
        std::cout << "Many additions test failed." << std::endl;
    }
    if (!test_many_removals()) {
        counter++;
        std::cout << "Many removals test failed." << std::endl;
    }
    if (!test_mixed()) {
        counter++;
        std::cout << "Mixed test failed." << std::endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

