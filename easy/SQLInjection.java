// Task description: What is an SQL injection? Write a method that is prone to
// SQL injection and discuss how developers can prevent this attack.
//
// Solution: The createQuery() method below inserts the username and password
// provided by the user in an SQL query to be run against the database. The aim
// is to authenticate the user by checking that the username and password match
// a row in the database. Because these strings come from an untrusted source,
// they make it possible to attack this application using SQL injection.
//
// A malicious user might insert "admin' OR 'A' == 'A" as username and a random
// password to attempt to log in as admin. This username value changes the SQL
// query in such a way that it will match the admin user regardless of the
// password provided. There are many variations of this attack depending on the
// form of the underlying SQL query and what the attacker wants to achieve. All
// of them have one flaw in common: they take data from an untrusted source and
// compile it into the program.
//
// There are two ways to solve this problem: either filter the input data to
// ensure it does not cause a security issue or avoid putting the input data in
// the executable context.
//
// The first method involves maintaining a list of potentially problematic text
// patterns and ensuring they do not appear in the input strings. This method is
// called blacklisting and has one major flaw: you can only protect the
// application against attacks that are already known. If a new form of attack
// is discovered, this method will not guarantee that the application is secure
// against it. There are a lot of ways to perform SQL injection, including using
// unusual character encodings, and new forms are continuously invented.
//
// The second method involves using prepared statements to query the database.
// This technique avoids putting the data in the executable context by pre-
// compiling the SQL statement with placeholders instead of the data. When the
// data is available, it is inserted in the prepared statement and executed
// safely against the database. Since compilation has already taken place, there
// is no way for an attacker to affect what will execute on the server. Prepared
// statements also improve performance, since queries that execute multiple
// times are parsed, compiled and optimized only once.
//
// The example below could be secured by using prepared statements as follows:
//
// statement = db.prepareStatement("select ID from USER where NAME = ? AND " +
//                                 "PASSWORD = ?;");
// statement.setString(1, username);
// statement.setString(2, password);
// return statement.executeQuery();
//
// An additional problem with this application is that it stores user passwords
// in the database in plain text. This is a major security risk because an
// attacker could potentially read the USER table and use the users' passwords
// to gain access to this application or other applications and sites. The
// solution to this problem is to hash the passwords using the cryptographically
// secure SHA-256 algorithm and only store the hashes. When the user wants to
// log in, we again need to hash the given password and compare it with the one
// already in the database. Even if an attacker gains access to the USER table,
// they will not be able to extract the passwords because it is computationally
// infeasible to reverse the hash function.
//
// Unfortunately the attacker could still attack the hashed passwords by brute
// force guessing. There are many lists that contain common passwords and their
// hashes online (rainbow tables). To further strengthen the application against
// this we can salt the cryptographic hashes by generating a random string per
// user and appending it to their password before generating the hash. The salt
// can be stored in the database as plain text, but because it is different for
// every user the attacker must attack each user's password separately. This
// renders rainbow tables useless. One other technique to make password cracking
// more difficult is to hash the password more than one times. Computation of
// the iterated hash once for each login has a relatively small performance cost
// for the application, but the cost of computing it billions of times to crack
// passwords is much greater.

public class SQLInjection {

    private static String createQuery(final String username,
                                      final String password) {

        return String.format("select ID from USER where NAME = '%s' " +
                "and PASSWORD = '%s';", username, password);
    }

    private static boolean testNoInjection() {
        String expected = "select ID from USER " +
                          "where NAME = 'Lee' " +
                          "and PASSWORD = '123';";
        String actual = createQuery("Lee", "123");
        return expected.equals(actual);
    }

    private static boolean testInjection() {
        String expected = "select ID from USER " +
                          "where NAME = 'admin' or 'A' = 'A' " +
                          "and PASSWORD = 'abc';";
        String actual = createQuery("admin' or 'A' = 'A", "abc");
        return expected.equals(actual);
    }


    public static void main(String[] args) {
        int counter = 0;
        if (!testNoInjection()) {
            System.out.println("No SQL injection test failed.");
            counter++;
        }
        if (!testInjection()) {
            System.out.println("SQL injection test failed.");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

