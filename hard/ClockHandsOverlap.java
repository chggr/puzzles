// Task description: A regular analog clock has an hour, a minute and a second
// hand. At midnight all three hands are exactly aligned. Create a program to
// simulate their movement and answer the following questions:
//
// (1) Which times in a day do all three hands overlap?
// (2) which times in a day do the hour and minute hands overlap?
//
// Solution: In the implementation below we first define class Time that is used
// to store a timestamp with millisecond accuracy. Method tick() moves the clock
// one millisecond forward and there are also methods to get the angle of every
// hand (millisecond / second / minute / hour) from the midnight position. To
// answer the given questions, we simulate the clock ticking one millisecond at
// a time and at each position we calculate the angles of each hand to identify
// whether they overlap or not.
//
// The result of the simulation is that all three hands overlap on just two
// occasions: at midnight and at noon. The hour and minute hands overlap on 22
// occasions. These answers can also be mathematically derived as follows:
//
// The minute hand covers 360 degrees in 60 minutes, thus its velocity is 6
// degrees per minute. The hour hand covers 360 degrees in 12 hours, thus its
// velocity is 30 degrees per hour or 0.5 degrees per minute. Therefore the
// relative angular velocity between these two hands will be 6 - 0.5 = 5.5 =
// 11/2 degrees per minute. The two hands will overlap every time the relative
// angular speed has covered 360 degrees, i.e. every 360 / (11/2) = 720 / 11 =
// 65.454545 minutes. The total number of times they will overlap in a day can
// be calculated as 24 * 60 / (720 / 11) == 22 times.

public class ClockHandsOverlap {

    private static final class Time {
        private final int hour;
        private final int minute;
        private final int second;
        private final int milli;

        public Time(int hour, int minute, int second, int milli) {
            if (hour < 0 || hour > 23 ||
                minute < 0 || minute > 59 ||
                second < 0 || second > 59 ||
                milli < 0 || milli > 999) {
                throw new IllegalArgumentException("Invalid time");
            }

            this.hour = hour;
            this.minute = minute;
            this.second = second;
            this.milli = milli;
        }

        public Time tick() {
            int newHour = hour;
            int newMinute = minute;
            int newSecond = second;
            int newMilli = milli;

            newMilli++;

            if (newMilli >= 1000) {
                newSecond++;
                newMilli = 0;
            }

            if (newSecond >= 60) {
                newMinute++;
                newSecond = 0;
            }

            if (newMinute >= 60) {
                newHour++;
                newMinute = 0;
            }

            if (newHour >= 24) {
                newHour = 0;
            }
            return new Time(newHour, newMinute, newSecond, newMilli);
        }

        public double getMilliHandAngle() {
            return 360.0 * milli / 1000.0;
        }

        public double getSecondHandAngle() {
            return 360.0 * second / 60.0 +
                   (getMilliHandAngle() / 360.0) * (360.0 / 60.0);
        }

        private double getMinuteHandAngle() {
            return 360.0 * minute / 60.0 +
                   (getSecondHandAngle() / 360.0) * (360.0 / 60.0);
        }

        private double getHourHandAngle() {
            return 360.0 * (hour >= 12 ? hour - 12 : hour) / 12.0 +
                   (getMinuteHandAngle() / 360.0) * (360.0 / 12.0);
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Time)) return false;

            Time other = (Time) o;
            return other.hour == this.hour &&
                   other.minute == this.minute &&
                   other.second == this.second &&
                   other.milli == this.milli;
        }

        @Override
        public String toString() {
            return hour + ":" + minute + ":" + second + "." + milli;
        }
    }

    private static boolean equals(double a, double b, double e) {
        return Math.abs(a - b) < e;
    }

    private static void allHandsOverlap() {
        Time midnight = new Time(0, 0, 0, 0);
        Time current = new Time(0, 0, 0, 0);

        do {
            if (equals(current.getSecondHandAngle(),
                       current.getMinuteHandAngle(), 0.0001) &&
                equals(current.getMinuteHandAngle(),
                       current.getHourHandAngle(), 0.0001)) {
                System.out.println(current);
            }

            current = current.tick();
        } while (!current.equals(midnight));
    }

    private static void hourMinuteHandsOverlap() {
        Time midnight = new Time(0, 0, 0, 0);
        Time current = new Time(0, 0, 0, 0);

        do {
            if (equals(current.getHourHandAngle(),
                       current.getMinuteHandAngle(), 0.00005)) {
                System.out.println(current);
            }

            current = current.tick();
        } while (!current.equals(midnight));
    }

    private static boolean testTimeTick() {
        Time secondTick = new Time(0, 0, 0, 999);
        Time minuteTick = new Time(0, 0, 59, 999);
        Time hourTick = new Time(0, 59, 59, 999);
        Time dayTick = new Time(23, 59, 59, 999);

        return new Time(0, 0, 1, 0).equals(secondTick.tick()) &&
               new Time(0, 1, 0, 0).equals(minuteTick.tick()) &&
               new Time(1, 0, 0, 0).equals(hourTick.tick()) &&
               new Time(0, 0, 0, 0).equals(dayTick.tick());
    }

    private static boolean testGetMilliHandAngle() {
        return 0.0 == new Time(0, 0, 0, 0).getMilliHandAngle() &&
               90.0 == new Time(0, 0, 0, 250).getMilliHandAngle() &&
               180.0 == new Time(0, 0, 0, 500).getMilliHandAngle() &&
               270.0 == new Time(0, 0, 0, 750).getMilliHandAngle() &&
               359.64 == new Time( 0, 0, 0, 999).getMilliHandAngle();
    }

    private static boolean testGetSecondHandAngle() {
        return 0.0 == new Time(0, 0, 0, 0).getSecondHandAngle() &&
               60.0 == new Time(0, 0, 10, 0).getSecondHandAngle() &&
               90.0 == new Time(0, 0, 15, 0).getSecondHandAngle() &&
               120.0 == new Time(0, 0, 20, 0).getSecondHandAngle() &&
               180.0 == new Time(0, 0, 30, 0).getSecondHandAngle() &&
               270.0 == new Time(0, 0, 45, 0).getSecondHandAngle() &&
               273.0 == new Time(0, 0, 45, 500).getSecondHandAngle();
    }

    private static boolean testGetMinuteHandAngle() {
        return 0.0 == new Time(0, 0, 0, 0).getMinuteHandAngle() &&
               60.0 == new Time(0, 10, 0, 0).getMinuteHandAngle() &&
               90.0 == new Time(0, 15, 0, 0).getMinuteHandAngle() &&
               120.0 == new Time(0, 20, 0, 0).getMinuteHandAngle() &&
               180.0 == new Time(0, 30, 0, 0).getMinuteHandAngle() &&
               270.0 == new Time(0, 45, 0, 0).getMinuteHandAngle() &&
               63.0 == new Time(0, 10, 30, 0).getMinuteHandAngle() &&
               63.05 == new Time(0, 10, 30, 500).getMinuteHandAngle() &&
               65.9999 == new Time(0, 10, 59, 999).getMinuteHandAngle();
    }

    private static boolean testGetHourHandAngle() {
        return 0.0 == new Time(0, 0, 0, 0).getHourHandAngle() &&
               60.0 == new Time(2, 0, 0, 0).getHourHandAngle() &&
               90.0 == new Time(3, 0, 0, 0).getHourHandAngle() &&
               120.0 == new Time(4, 0, 0, 0).getHourHandAngle() &&
               180.0 == new Time(6, 0, 0, 0).getHourHandAngle() &&
               270.0 == new Time(9, 0, 0, 0).getHourHandAngle() &&
               35.0 == new Time(1, 10, 0, 0).getHourHandAngle() &&
               35.25 == new Time(1, 10, 30, 0).getHourHandAngle() &&
               35.375 == new Time(1, 10, 45, 0).getHourHandAngle() &&
               35.38 == new Time(1, 10, 45, 600).getHourHandAngle();
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testTimeTick()) {
            System.out.println("Time tick test failed!");
            counter++;
        }
        if (!testGetMilliHandAngle()) {
            System.out.println("Get millisecond hand angle test failed!");
            counter++;
        }
        if (!testGetSecondHandAngle()) {
            System.out.println("Get second hand angle test failed!");
            counter++;
        }
        if (!testGetMinuteHandAngle()) {
            System.out.println("Get minute hand angle test failed!");
            counter++;
        }
        if (!testGetHourHandAngle()) {
            System.out.println("Get hour hand angle test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");

        System.out.println("\nAll hands will overlap at:");
        allHandsOverlap();

        System.out.println("\nHour and minute hands will overlap at:");
        hourMinuteHandsOverlap();
    }
}

