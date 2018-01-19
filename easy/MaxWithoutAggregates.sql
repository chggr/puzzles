/* Task description: Given the following SQL database schema, write an SQL
   statement that returns the maximum value from the table without using any
   aggregates such as MAX or MIN and also ORDER BY.

   DATA(
     num INTEGER(4)
   );

   Solution: In the solution below, the inner select statement will return all
   numbers in the table where there exists at least one other number that is
   greater. The top level select statement will simply select the number that
   does not have any other numbers greater than it, thus is the maximum number
   in the table. The distinct keyword is used so that we get one result even if
   the maximum number might appear multiple times.
*/

SELECT DISTINCT num
FROM DATA
WHERE num NOT IN (
    SELECT lesser.num
    FROM DATA lesser, DATA greater
    WHERE lesser.num < greater.num
)

