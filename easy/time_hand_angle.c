#include <stdio.h>

// Task description: Given an analog clock, implement an algorithm to calculate
// the angle between the hour and minute hands. Negative angle denotes anti
// clockwise direction.
//
// E.g. For input 0 and 0 the method should return 0.0
//      For input 1 and 20 the method should return 80.0 
//      For input 9 and 10 the method should return -215

double calculate_angle(unsigned int hour, unsigned int minute) {
    if (hour > 12 || minute > 59) return -1.0;
    double minute_angle = (minute / 60.0) * 360.0;
    double hour_angle = (hour / 12.0) * 360.0 + (minute / 60.0) * 360.0 / 12;
    return minute_angle - hour_angle;
}

int test_invalid_hour() {
    return -1.0 == calculate_angle(13, 0);
}

int test_invalid_minute() {
    return -1.0 == calculate_angle(0, 60);
}

int test_positive_angle() {
    return 80.0 == calculate_angle(1, 20);
}

int test_negative_angle() {
    return -215.0 == calculate_angle(9, 10);
}

int test_zero_angle() {
    return 0.0 == calculate_angle(0, 0);
}

void main() {
    int counter = 0;
    if (!test_invalid_hour()) {
        counter++;
        printf("Invalid hour test failed!\n");
    }
    if (!test_invalid_minute()) {
        counter++;
        printf("Invalid minute test failed!\n");
    }
    if (!test_positive_angle()) {
        counter++;
        printf("Positive angle test failed!\n");
    }
    if (!test_negative_angle()) {
        counter++;
        printf("Negative angle test failed!\n");
    }
    if (!test_zero_angle()) {
        counter++;
        printf("Zero angle test failed!\n");
    }
    printf("%d tests failed.\n", counter);
}

