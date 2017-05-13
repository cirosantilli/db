---
title: SELECT
---

Choose certain table columns to take further actions on them. Returns chosen columns.

Print all data of column `col` of table `table`:

    SELECT COLUMN col FROM table;

Print all data of columns `col0` and `col1` of table `table`:

    SELECT col0,col1 FROM table;

Show entire table `table`:

    SELECT * FROM table;

## Rename table

It is possible to rename tables on the select:

    CREATE TABLE t (i INT);
    INSERT INTO t VALUES (1), (2);
    SELECT new_name.i FROM t new_name ORDER BY new_name.i;
    DROP TABLE t;

Output:

    i
    1
    2

This can be useful to disambiguate when joining a table with itself.

## Column that is a function of other columns

It is possible generate a selection that is a function of the row values:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 0), (0, 1), (1, 2), (-1, 3);
    SELECT c0, c0 + c1, c0 FROM t;
    DROP TABLE t;

Output:

    +------+---------+------+
    | c0   | c0 + c1 | c0   |
    +------+---------+------+
    |    0 |       0 |    0 |
    |    0 |       1 |    0 |
    |    1 |       3 |    1 |
    |   -1 |       2 |   -1 |
    +------+---------+------+

## Single values

Besides selecting rows from columns, `SELECT` can also select single values or expressions.

These are treated as if they were rows with the same name as the input expression.

    SELECT 1;

Output:

    +---+
    | 1 |
    +---+
    | 1 |
    +---+

Input:

    SELECT 1 + 1;

    +-------+
    | 1 + 1 |
    +-------+
    |     2 |
    +-------+

It is also possible to generate multiple rows as:

    SELECT 1,2

Output:

    +---+---+
    | 1 | 2 |
    +---+---+
    | 1 | 2 |
    +---+---+

Multiple rows can be achieved with:

    SELECT 1,2,3
    UNION ALL
    SELECT 4,5,6;

Output:

    +---+---+---+
    | 1 | 2 | 3 |
    +---+---+---+
    | 4 | 5 | 6 |
    +---+---+---+

## WHERE

Filter only certain rows.

Any function or operator that returns a boolean can be used by substituting the value of the row by its name (`c0`, `c1`, etc.):

It is not possible to refer to a column that have be created in the query via `AS` or an aggregate function on the same command as in `(1)` and `(2)`.

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 0), (0, 1), (1, 0), (2, 0);
    SELECT * FROM t WHERE c0 = 0;
    SELECT * FROM t WHERE c0 <> 0;
    SELECT * FROM t WHERE c0 BETWEEN 0 AND 1;
    SELECT * FROM t WHERE c0 IN(0, 2);
    SELECT * FROM t WHERE c0 > 0 AND C0 < 2;
    SELECT * FROM t WHERE c0 > 0 AND NOT (C0 > 2);
    SELECT * FROM t WHERE c0 = 0 OR c0 = 2;
    SELECT c0+c1 AS sum FROM t WHERE sum > 0;     #(1)
    SELECT c0+c1        FROM t WHERE `c0+c1` > 0; #(2)
    DROP TABLE t;

It would of course be possible to get all the results and then filter them using a programming language, but the list of all results might be too long.

## DISTINCT

Only show each value of a column tuple once:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 0), (0, 1), (1, 0), (1, 0);
    SELECT DISTINCT c0    FROM t ORDER BY c0;
    SELECT DISTINCT c0,c1 FROM t ORDER BY c0,c1;
    SELECT DISTINCT *     FROM t ORDER BY c0,c1;
    DROP TABLE t;

Output:

    c0
    0
    1

    c0   c1
    0    0
    0    1
    1    0

    c0   c1
    0    0
    0    1
    1    0

`SELECT DISTINCT` is applied after aggregate functions, so you probably don't to use them together.

If you want to do that, consider one of the following solutions:

- the `DISTICT` form of the aggregate function `SUM(DISTINCT )`,
- subquery
- `GROUP BY`. Can be used to emulate `DISTINCT`, the only problem is that you have to type all columns twice.

Examples:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 0), (0, 1), (1, 0), (1, 0);
    SELECT DISTINCT SUM(c0) FROM t;
    SELECT SUM(DISTINCT c0) FROM t;
    SELECT SUM(t2.c0) FROM (SELECT DISTINCT c0 FROM t) AS t2;
    DROP TABLE t;

Output:

    SUM(c0)
    2

    SUM(DISTINCT c0)
    1

    SUM(t2.c0)
    1

## Prepared statements

- <http://stackoverflow.com/questions/675010/what-is-the-question-marks-significance-in-mysql>
- <http://dev.mysql.com/doc/refman/5.0/en/sql-syntax-prepared-statements.html>

Syntax error because of missing quote:

    SELECT * FROM t WHERE s = ?;

With quote, it has no special meaning:

    CREATE TABLE t (s CHAR(1));
    INSERT INTO t VALUES ('a');
    INSERT INTO t VALUES ("?");
    SELECT * FROM t WHERE s = '?';
    DROP TABLE t;

Output:

    s
    ?

Strings are escaped:

    CREATE TABLE t (s CHAR(1));
    INSERT INTO t VALUES ('a');
    INSERT INTO t VALUES ("'");
    PREPARE stmt1 FROM 'SELECT * FROM t WHERE s = ?';
    SET @a = "'";
    EXECUTE stmt1 USING @a;
    DROP TABLE t;

Output:

    s
    '

## Subqueries

Select can also work on query results output from other commands such as other `SELECT` or `UNION`.

`WHERE` + `IN`:

    CREATE TABLE t (c0 INT);
    INSERT INTO t VALUES (0), (1), (2);
    SELECT * FROM t WHERE c0 < 2 AND c0 IN (
        SELECT * FROM t WHERE c0 > 0
    );
    DROP TABLE t;

Output:

    c0
    1

It is mandatory to rename the subquery as something using `AS` or else this produces an error.

OK:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT MAX(c0) FROM (
        SELECT c0 FROM t
    ) AS t2;
    DROP TABLE t;

Output:

    MAX(c0)
    3

Error:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT MAX(c0) FROM (
        SELECT c0 FROM t
    );
    DROP TABLE t;

`WHERE` + `MAX` to get the row where a given value is maximum:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT * FROM t WHERE c0 = (
        SELECT MAX(c0) FROM t
    );
    DROP TABLE t;

Output:

    c0  c1
    3   9

## AS

Rename columns and subquery tables.

Rename columns:

    SELECT 1 AS one, 2 AS two;

Output:

    one two
    1   2

The `AS` keyword is not mandatory, but is considered by the manual itself to be better style.

    SELECT 1 one, 2 two;

Output:

    one two
    1   2

Useful to reduce code duplication:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT MAX(sum) FROM (
        SELECT c0 + c1 AS sum FROM t WHERE c0 > 0
    ) AS t2;
    DROP TABLE t;

Output:

    MAX(sum)
    12

It would also be possible to do the same via:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT MAX(`c0 + c1`) FROM (
        SELECT c0 + c1 FROM t WHERE c0 > 0
    ) AS t2;
    DROP TABLE t;

Output:

    MAX(`c0 + c1`)
    12

but that would be bad since it duplicates the calculation code `c0 + c1`.

The above example is not the best way to achieve this task since `MAX(c0 + c1)` would work too.

Mandatory to rename subqueries. See subquery.

Useful to disambiguate output headers when there are multiple tables with identical column names:

    CREATE TABLE t  (i INT);
    CREATE TABLE t2 (i INT);
    INSERT INTO t VALUES  (1);
    INSERT INTO t2 VALUES (2);
    # Ambiguous header names.
    SELECT * FROM t, t2 ORDER BY t.i, t2.i;
    # Not ambiguous header names.
    SELECT t.i AS `t.i`, t2.i AS `t2.i` FROM t, t2;
    DROP TABLE t, t2;

Output:

    t   t
    1   2

    t.i t2.i
    1   2

Renaming tables is useful to reduce code size:

    CREATE TABLE long_table_name1 (i INT);
    CREATE TABLE long_table_name2 (j INT);
    INSERT INTO long_table_name1 VALUES (1);
    INSERT INTO long_table_name2 VALUES (2);
    SELECT t1.i, t2.i
        FROM long_table_name1 AS t1, long_table_name2 AS t2
        ORDER BY t1.i, t2.i;
    DROP TABLE long_table_name1, long_table_name2;

Output:

    i   j
    1   2

### Reuse AS

Goal:

    SELECT 1 AS one, one AS two;

<http://stackoverflow.com/questions/6085443/can-i-resuse-a-calculated-field-in-a-select-query>
