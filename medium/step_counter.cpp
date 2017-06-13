#include <iostream>

// Task description: A young kid can climb up the stairs three, two or one
// steps at a time. If a staircase has a given number of steps, write a method
// that counts how many different ways the kid can climb it up.
//
// E.g. If there are 2 steps, the answer is 2: 11 2
//      If there are 3 steps, the asnwer is 4: 111 21 12 3
//      If there are 4 steps, the answer is 7: 1111 211 121 112 22 31 13
//      If there are 5 steps, the asnwer is 13: 11111 2111 1211 1121 1112 221
//                                              212 122 311 131 113 32 23

int count(int steps) {
	if (steps > 3) {
		return count(steps-3) + count(steps-2) + count(steps-1);
	} else if (steps == 3) {
		return 1 + count(steps-2) + count(steps-1);
	} else if (steps == 2) {
		return 1 + count(steps-1);
	} else if (steps == 1) {
		return 1;
	}
	return 0;
}

bool test_zero_steps() {
	return count(0) == 0;
}

bool test_one_step() {
	return count(1) == 1;
}

bool test_two_steps() {
	return count(2) == 2;
}

bool test_three_steps() {
	return count(3) == 4;
}

bool test_four_steps() {
	return count(4) == 7;
}

bool test_five_steps() {
	return count(5) == 13;
}

int main() {
	int counter = 0;
	if (!test_zero_steps()) {
		std::cout << "Zero step test failed!\n";
		counter++;
	}
	if (!test_one_step()) {
		std::cout << "One step test failed!\n";
		counter++;
	}
	if (!test_two_steps()) {
		std::cout << "Two steps test failed!\n";
		counter++;
	}
	if (!test_three_steps()) {
		std::cout << "Three steps test failed!\n";
		counter++;
	}
	if (!test_four_steps()) {
		std::cout << "Four steps test failed!\n";
		counter++;
	}
	if (!test_five_steps()) {
		std::cout << "Five steps test failed!\n";
		counter++;
	}
	std::cout << counter << " tests failed.\n";
}
